/**
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */
#include <catch.hpp>

#include "ProtocolUtil.h"
#include "TransportTestObject.h"

#include <opendnp3/transport/TransportConstants.h>

using namespace std;
using namespace openpal;
using namespace opendnp3;

#define SUITE(name) "TransportLayerTestSuite - " name

// make sure an invalid state exception gets thrown
// for every event other than LowerLayerUp() since
// the layer starts in the online state
TEST_CASE(SUITE("StateOffline"))
{
	TransportTestObject test;

	test.upper.SendDown("00");
	REQUIRE(test.log.PopOneEntry(flags::ERR));
	test.link.SendUp("");
	REQUIRE(test.log.PopOneEntry(flags::ERR));
	test.transport.OnSendResult(true);
	REQUIRE(test.log.PopOneEntry(flags::ERR));
	test.transport.OnLowerLayerDown();
	REQUIRE(test.log.PopOneEntry(flags::ERR));
}

TEST_CASE(SUITE("StateReady"))
{
	TransportTestObject test(true); //makes an implicit call to 'test.link.ThisLayerUp()'

	//check that that the transport layer is correctly forwarding up/down
	REQUIRE(test.upper.IsOnline());
	test.transport.OnLowerLayerDown();
	REQUIRE_FALSE(test.upper.IsOnline());
	test.transport.OnLowerLayerUp();
	REQUIRE(test.upper.IsOnline());

	// check that these actions all log errors
	test.transport.OnLowerLayerUp();
	REQUIRE(test.log.PopOneEntry(flags::ERR));
	test.transport.OnSendResult(true);
	REQUIRE(test.log.PopOneEntry(flags::ERR));
}

TEST_CASE(SUITE("ReceiveBadArguments"))
{
	TransportTestObject test(true);

	//check that the wrong aruments throw argument exceptions, and it's doesn't go to the sending state
	test.link.SendUp("");
	REQUIRE(TLERR_NO_PAYLOAD ==  test.log.NextErrorCode());
	test.link.SendUp("FF");
	REQUIRE(TLERR_NO_PAYLOAD ==  test.log.NextErrorCode());

	test.link.SendUp(test.GetData("C0", 0, 250)); // length 251

	REQUIRE(TLERR_TOO_MUCH_DATA ==  test.log.NextErrorCode());
}

TEST_CASE(SUITE("ReceiveNoPayload"))
{
	TransportTestObject test(true);
	//try sending a FIR/FIN packet with no payload (1 byte)
	test.link.SendUp("C0"); // FIR/FIN
	REQUIRE(test.log.NextErrorCode() ==  TLERR_NO_PAYLOAD);
}

TEST_CASE(SUITE("ReceiveNoFIR"))
{
	TransportTestObject test(true);
	//try sending a non-FIR w/ no prior packet
	test.link.SendUp("80 77"); // _/FIN
	REQUIRE(test.log.NextErrorCode() ==  TLERR_MESSAGE_WITHOUT_FIR);
}

TEST_CASE(SUITE("ReceiveWrongSequence"))
{
	TransportTestObject test(true);
	//send a FIR, followed by a FIN w/ the wrong sequence
	test.link.SendUp(test.GetData("40")); // FIR/_/0
	test.link.SendUp(test.GetData("82")); // _/FIN/2
	REQUIRE(test.log.NextErrorCode() ==  TLERR_BAD_SEQUENCE);
}

TEST_CASE(SUITE("PacketsCanBeOfVaryingSize"))
{
	TransportTestObject test(true);
	test.link.SendUp("40 0A 0B 0C"); // FIR/_/0
	REQUIRE(test.log.IsLogErrorFree());
	test.link.SendUp("81 0D 0E 0F"); // _/FIN/1
	REQUIRE(test.log.IsLogErrorFree());
	REQUIRE("0A 0B 0C 0D 0E 0F" ==  test.upper.GetBufferAsHexString());
}

TEST_CASE(SUITE("ReceiveSinglePacket"))
{
	TransportTestObject test(true);
	//now try receiving 1 a single FIR/FIN with a magic value
	test.link.SendUp("C0 77");
	REQUIRE("77" ==  test.upper.GetBufferAsHexString());
}

TEST_CASE(SUITE("ReceiveLargestPossibleAPDU"))
{
	TransportTestObject test(true);

	uint32_t num_packets = CalcMaxPackets(opendnp3::sizes::DEFAULT_APDU_BUFFER_SIZE, TL_MAX_TPDU_PAYLOAD);
	uint32_t last_packet_length = CalcLastPacketSize(opendnp3::sizes::DEFAULT_APDU_BUFFER_SIZE, TL_MAX_TPDU_PAYLOAD);

	vector<string> packets;
	string apdu = test.GeneratePacketSequence(packets, num_packets, last_packet_length);
	for(string s : packets)
	{
		test.link.SendUp(s);
	}

	REQUIRE(test.log.IsLogErrorFree());
	REQUIRE(test.upper.BufferEqualsHex(apdu)); //check that the correct data was written
}

TEST_CASE(SUITE("ReceiveBufferOverflow"))
{
	TransportTestObject test(true);

	uint32_t num_packets = CalcMaxPackets(opendnp3::sizes::DEFAULT_APDU_BUFFER_SIZE, TL_MAX_TPDU_PAYLOAD);
	uint32_t last_packet_length = CalcLastPacketSize(opendnp3::sizes::DEFAULT_APDU_BUFFER_SIZE, TL_MAX_TPDU_PAYLOAD);

	//send 1 more packet than possible
	vector<string> packets;
	string apdu = test.GeneratePacketSequence(packets, num_packets + 1, last_packet_length);
	for(string s : packets)
	{
		test.link.SendUp(s);
	}

	REQUIRE(test.upper.IsBufferEmpty());
	REQUIRE(test.log.NextErrorCode() ==  TLERR_BUFFER_FULL);
}

TEST_CASE(SUITE("ReceiveNewFir"))
{
	TransportTestObject test(true);

	test.link.SendUp(test.GetData("40"));	// FIR/_/0
	REQUIRE(test.upper.IsBufferEmpty());

	test.link.SendUp("C0 AB CD");	// FIR/FIN/0
	REQUIRE("AB CD" ==  test.upper.GetBufferAsHexString());
	REQUIRE(test.log.NextErrorCode() == TLERR_NEW_FIR_MID_SEQUENCE); //make sure it logs the dropped frames
}

TEST_CASE(SUITE("SendArguments"))
{
	TransportTestObject test(true);
	test.upper.SendDown("");
	REQUIRE(test.log.PopOneEntry(flags::ERR));
}

TEST_CASE(SUITE("StateSending"))
{
	TransportTestObject test(true);

	// this puts the layer into the Sending state
	test.upper.SendDown("11");
	REQUIRE("C0 11" ==  test.link.PopWriteAsHex()); //FIR/FIN SEQ=0

	// Check that while we're sending, all other send requests are rejected
	test.upper.SendDown("00");
	REQUIRE(test.log.PopUntil(flags::ERR));
	test.transport.OnLowerLayerUp();
	REQUIRE(test.log.PopUntil(flags::ERR));

	//while we are sending, we should still be able to receive data as normal
	test.link.SendUp("C0 77");
	test.upper.BufferEqualsHex("77");

	//this should put us back in the Ready state since it was a single tpdu send
	test.transport.OnSendResult(true);
	REQUIRE(test.upper.GetState().mSuccessCnt ==  1);

	test.transport.OnSendResult(true);
	REQUIRE(test.log.PopUntil(flags::ERR));
}

TEST_CASE(SUITE("SendFailure"))
{
	TransportTestObject test(true);

	// this puts the layer into the Sending state
	test.upper.SendDown("11");
	REQUIRE("C0 11" ==  test.link.PopWriteAsHex()); //FIR/FIN SEQ=0

	//this should put us back in the Ready state
	test.transport.OnSendResult(false);
	REQUIRE(test.upper.GetState().mSuccessCnt ==  0);
	REQUIRE(test.upper.GetState().mFailureCnt ==  1);

	test.upper.SendDown("11");
	REQUIRE("C1 11" ==  test.link.PopWriteAsHex()); // use next sequence number FIR/FIN SEQ=1
	test.transport.OnSendResult(true);
	REQUIRE(test.upper.GetState().mSuccessCnt ==  1);
	REQUIRE(test.upper.GetState().mFailureCnt ==  1);
}

TEST_CASE(SUITE("SendSuccess"))
{
	TransportTestObject test(true);

	// this puts the layer into the Sending state
	test.upper.SendDown("11");
	REQUIRE("C0 11" ==  test.link.PopWriteAsHex()); //FIR/FIN SEQ=0
	test.transport.OnSendResult(true);

	// this puts the layer into the Sending state
	test.upper.SendDown("11");
	REQUIRE("C1 11" ==  test.link.PopWriteAsHex()); //FIR/FIN SEQ=1
	test.transport.OnSendResult(true);
	REQUIRE(test.upper.GetState().mSuccessCnt ==  2);
}

//if we're in the middle of a send and the layer goes down
TEST_CASE(SUITE("ClosedWhileSending"))
{
	TransportTestObject test(true);
	test.upper.SendDown("11"); //get the layer into the sending state

	test.transport.OnLowerLayerDown();
	REQUIRE_FALSE(test.upper.IsOnline());
}

TEST_CASE(SUITE("SendFullAPDU"))
{
	TransportTestObject test(true);

	uint32_t numPackets = CalcMaxPackets(opendnp3::sizes::DEFAULT_APDU_BUFFER_SIZE, TL_MAX_TPDU_PAYLOAD);
	uint32_t lastPacketLength = CalcLastPacketSize(opendnp3::sizes::DEFAULT_APDU_BUFFER_SIZE, TL_MAX_TPDU_PAYLOAD);

	vector<string> packets;
	std::string apdu = test.GeneratePacketSequence(packets, numPackets, lastPacketLength);

	test.upper.SendDown(apdu);

	// 9 total packets
	REQUIRE(numPackets ==  test.link.sends.size());
	REQUIRE(packets.size() == test.link.sends.size());

	for (size_t i = 0; i < packets.size(); ++i)
	{
		REQUIRE(packets[i] == test.link.PopWriteAsHex());
	}

	test.transport.OnSendResult(true);
}



