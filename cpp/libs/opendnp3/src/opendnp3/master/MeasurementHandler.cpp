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
#include "MeasurementHandler.h"

#include "opendnp3/app/APDUParser.h"

#include <openpal/logging/LogMacros.h>

using namespace openpal;

namespace opendnp3
{

bool MeasurementHandler::ProcessMeasurements(const openpal::ReadOnlyBuffer& objects, openpal::Logger* pLogger, ISOEHandler* pHandler)
{
	MeasurementHandler handler(*pLogger, pHandler);
	auto result = APDUParser::ParseTwoPass(objects, &handler, pLogger);
	return (result == APDUParser::Result::OK);
}

MeasurementHandler::MeasurementHandler(const openpal::Logger& logger, ISOEHandler* pSOEHandler_) : 
	APDUHandlerBase(logger),
	txInitiated(false),
	pSOEHandler(pSOEHandler_)
{
	
}

MeasurementHandler::~MeasurementHandler()
{
	if (txInitiated)
	{
		Transaction::End(pSOEHandler);
	}
}

void MeasurementHandler::CheckForTxStart()
{
	if (!txInitiated)
	{
		txInitiated = true;
		Transaction::Start(pSOEHandler);
	}
}

void MeasurementHandler::_OnRange(const HeaderRecord& record, const IterableBuffer<IndexedValue<Binary, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadStatic(meas);
}

void MeasurementHandler::_OnRange(const HeaderRecord& record, const IterableBuffer<IndexedValue<DoubleBitBinary, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadStatic(meas);
}

void MeasurementHandler::_OnRange(const HeaderRecord& record, const IterableBuffer<IndexedValue<BinaryOutputStatus, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadStatic(meas);
}

void MeasurementHandler::_OnRange(const HeaderRecord& record, const IterableBuffer<IndexedValue<Counter, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadStatic(meas);
}

void MeasurementHandler::_OnRange(const HeaderRecord& record, const IterableBuffer<IndexedValue<FrozenCounter, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadStatic(meas);
}

void MeasurementHandler::_OnRange(const HeaderRecord& record, const IterableBuffer<IndexedValue<Analog, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadStatic(meas);
}

void MeasurementHandler::_OnRange(const HeaderRecord& record, const IterableBuffer<IndexedValue<AnalogOutputStatus, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadStatic(meas);
}

void MeasurementHandler::_OnRange(const HeaderRecord& record, const IterableBuffer<IndexedValue<OctetString, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadStatic(meas);
}

void MeasurementHandler::_OnIndexPrefix(const HeaderRecord& record, const IterableBuffer<IndexedValue<Binary, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadEvent(meas);
}

void MeasurementHandler::_OnIndexPrefix(const HeaderRecord& record, const IterableBuffer<IndexedValue<BinaryOutputStatus, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadEvent(meas);
}

void MeasurementHandler::_OnIndexPrefix(const HeaderRecord& record, const IterableBuffer<IndexedValue<DoubleBitBinary, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadEvent(meas);
}

void MeasurementHandler::_OnIndexPrefix(const HeaderRecord& record, const IterableBuffer<IndexedValue<Counter, uint16_t>>& meas)
{
	pSOEHandler->LoadEvent(meas);
}

void MeasurementHandler::_OnIndexPrefix(const HeaderRecord& record, const IterableBuffer<IndexedValue<FrozenCounter, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadEvent(meas);
}

void MeasurementHandler::_OnIndexPrefix(const HeaderRecord& record, const IterableBuffer<IndexedValue<Analog, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadEvent(meas);
}

void MeasurementHandler::_OnIndexPrefix(const HeaderRecord& record, const IterableBuffer<IndexedValue<AnalogOutputStatus, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadEvent(meas);
}

void MeasurementHandler::_OnIndexPrefix(const HeaderRecord& record, const IterableBuffer<IndexedValue<OctetString, uint16_t>>& meas)
{
	this->CheckForTxStart();
	pSOEHandler->LoadEvent(meas);
}

}


