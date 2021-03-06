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
#ifndef __LOOP_BACK_PHYSICAL_LAYER_H_
#define __LOOP_BACK_PHYSICAL_LAYER_H_

#include <asiopal/PhysicalLayerASIO.h>

#include <openpal/channel/IPhysicalLayerCallbacks.h>

#include <queue>

namespace asio
{
class io_service;
}

namespace opendnp3
{

// Provides a backend for testing physical layers
class LoopbackPhysicalLayer : public asiopal::PhysicalLayerASIO
{
public:
	LoopbackPhysicalLayer(openpal::LogRoot& root, asio::io_service& service);


private:

	void DoOpen();
	void DoClose();
	void DoOpenSuccess();
	void DoRead(openpal::WriteBuffer&);
	void DoWrite(const openpal::ReadOnlyBuffer&);


	void CheckForReadDispatch();

	std::deque<uint8_t> mWritten;

	openpal::WriteBuffer mBytesForReading;
};
}

#endif
