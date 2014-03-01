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
#ifndef __MOCK_APDU_HEADER_HANDLER_H_
#define __MOCK_APDU_HEADER_HANDLER_H_

#include <opendnp3/IAPDUHandler.h>

#include <vector>

namespace opendnp3
{

class MockApduHeaderHandler : public IAPDUHandler
{
	public:

		MockApduHeaderHandler()
		{}

		virtual void AllObjects(GroupVariation gv) override
		{
			groupVariations.push_back(gv);			
		}

		virtual void OnRangeRequest(GroupVariation gv, const StaticRange& range) override
		{
			groupVariations.push_back(gv);			
		}

		virtual void OnCountRequest(GroupVariation gv, uint32_t count) override
		{
			groupVariations.push_back(gv);			
		}

		virtual void OnIIN(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<bool, uint16_t>>& bits) override
		{
			groupVariations.push_back(gv);			
			bits.foreach([&](const IndexedValue<bool, uint16_t>& v) { iinBits.push_back(v); });
		}

		virtual void OnCountOf(const IterableBuffer<Group50Var1>& times) override
		{
			groupVariations.push_back(GroupVariation::Group50Var1);  // TODO - normalize this record keeping?			
		}

		virtual void OnCountOf(const IterableBuffer<Group52Var2>& times) override
		{
			groupVariations.push_back(GroupVariation::Group52Var2);  // TODO - normalize this record keeping?			
		}
				
		virtual void OnRange(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<Binary, uint16_t>>& meas) override
		{
			groupVariations.push_back(gv);			
			meas.foreach([&](const IndexedValue<Binary, uint16_t>& v) { staticBinaries.push_back(v); });
		}		

		

		virtual void OnRange(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<BinaryOutputStatus, uint16_t>>& meas) override
		{
			groupVariations.push_back(gv);			
			meas.foreach([&](const IndexedValue<BinaryOutputStatus, uint16_t>& v) { staticControlStatii.push_back(v); });
		}

		virtual void OnRange(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<Counter, uint16_t>>& meas) override
		{
			groupVariations.push_back(gv);			
			meas.foreach([&](const IndexedValue<Counter, uint16_t>& v) { staticCounters.push_back(v); });
		}

		virtual void OnRange(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<Analog, uint16_t>>& meas)  override
		{
			groupVariations.push_back(gv);			
			meas.foreach([&](const IndexedValue<Analog, uint16_t>& v) { eventAnalogs.push_back(v); });
		}
				
		virtual void OnRange(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<AnalogOutputStatus, uint16_t>>& meas) override
		{
			groupVariations.push_back(gv);			
			meas.foreach([&](const IndexedValue<AnalogOutputStatus, uint16_t>& v) { staticSetpointStatii.push_back(v); });
		}

		virtual void OnRange(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<OctetString, uint16_t>>& meas) override
		{
			groupVariations.push_back(gv);
			meas.foreach([&](const IndexedValue<OctetString, uint16_t>& v) { rangedOctets.push_back(v); });
		}


		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<Binary, uint16_t>>& meas) override
		{
			groupVariations.push_back(gv);
			meas.foreach([&](const IndexedValue<Binary, uint16_t>& v) { eventBinaries.push_back(v); });
		}

		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<Counter, uint16_t>>& meas)  override
		{
			groupVariations.push_back(gv);
			meas.foreach([&](const IndexedValue<Counter, uint16_t>& v) { eventCounters.push_back(v); });
		}

		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<Analog, uint16_t>>& meas)  override
		{
			groupVariations.push_back(gv);
			meas.foreach([&](const IndexedValue<Analog, uint16_t>& v) { eventAnalogs.push_back(v); });
		}

		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<OctetString, uint16_t>>& meas) override
		{
			groupVariations.push_back(gv);
			meas.foreach([&](const IndexedValue<OctetString, uint16_t>& v) { indexPrefixedOctets.push_back(v); });
		}

		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<Binary, uint8_t>>& meas) override
		{
			groupVariations.push_back(gv);
			meas.foreach([&](const IndexedValue<Binary, uint8_t>& v) { eventBinaries.push_back(v.Widen<uint16_t>()); });
		}

		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<Counter, uint8_t>>& meas)  override
		{
			groupVariations.push_back(gv);
			meas.foreach([&](const IndexedValue<Counter, uint8_t>& v) { eventCounters.push_back(v.Widen<uint16_t>()); });
		}

		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<Analog, uint8_t>>& meas)  override
		{
			groupVariations.push_back(gv);
			meas.foreach([&](const IndexedValue<Analog, uint8_t>& v) { eventAnalogs.push_back(v.Widen<uint16_t>()); });
		}

		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<OctetString, uint8_t>>& meas) override
		{
			groupVariations.push_back(gv);
			meas.foreach([&](const IndexedValue<OctetString, uint8_t>& v) { indexPrefixedOctets.push_back(v.Widen<uint16_t>()); });
		}

		void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<ControlRelayOutputBlock, uint16_t>>& meas) override
		{
			groupVariations.push_back(gv);			
			meas.foreach([&](const IndexedValue<ControlRelayOutputBlock, uint16_t>& v) { crobRequests.push_back(v); });
		}

		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<AnalogOutputInt16, uint16_t>>& meas) override
		{
			groupVariations.push_back(gv);			
			meas.foreach([&](const IndexedValue<AnalogOutputInt16, uint16_t>& v) { aoInt16Requests.push_back(v); });
		}
		
		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<AnalogOutputInt32, uint16_t>>& meas) override
		{
			groupVariations.push_back(gv);		
			meas.foreach([&](const IndexedValue<AnalogOutputInt32, uint16_t>& v) { aoInt32Requests.push_back(v); });
		}
		
		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<AnalogOutputFloat32, uint16_t>>& meas) override
		{
			groupVariations.push_back(gv);			
			meas.foreach([&](const IndexedValue<AnalogOutputFloat32, uint16_t>& v) { aoFloat32Requests.push_back(v); });
		}
		
		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<AnalogOutputDouble64, uint16_t>>& meas) override
		{
			groupVariations.push_back(gv);			
			meas.foreach([&](const IndexedValue<AnalogOutputDouble64, uint16_t>& v) { aoDouble64Requests.push_back(v); });
		}

		void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<ControlRelayOutputBlock, uint8_t>>& meas) override
		{
			groupVariations.push_back(gv);
			meas.foreach([&](const IndexedValue<ControlRelayOutputBlock, uint8_t>& v) { crobRequests.push_back(v.Widen<uint16_t>()); });
		}

		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<AnalogOutputInt16, uint8_t>>& meas) override
		{
			groupVariations.push_back(gv);
			meas.foreach([&](const IndexedValue<AnalogOutputInt16, uint8_t>& v) { aoInt16Requests.push_back(v.Widen<uint16_t>()); });
		}

		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<AnalogOutputInt32, uint8_t>>& meas) override
		{
			groupVariations.push_back(gv);
			meas.foreach([&](const IndexedValue<AnalogOutputInt32, uint8_t>& v) { aoInt32Requests.push_back(v.Widen<uint16_t>()); });
		}

		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<AnalogOutputFloat32, uint8_t>>& meas) override
		{
			groupVariations.push_back(gv);
			meas.foreach([&](const IndexedValue<AnalogOutputFloat32, uint8_t>& v) { aoFloat32Requests.push_back(v.Widen<uint16_t>()); });
		}

		virtual void OnIndexPrefix(GroupVariation gv, QualifierCode qualifier, const IterableBuffer<IndexedValue<AnalogOutputDouble64, uint8_t>>& meas) override
		{
			groupVariations.push_back(gv);
			meas.foreach([&](const IndexedValue<AnalogOutputDouble64, uint8_t>& v) { aoDouble64Requests.push_back(v.Widen<uint16_t>()); });
		}				
				
		std::vector<GroupVariation> groupVariations;

		std::vector<IndexedValue<bool, uint16_t>> iinBits;

		std::vector<IndexedValue<Binary, uint16_t>> eventBinaries;
		std::vector<IndexedValue<Binary, uint16_t>> staticBinaries;

		std::vector<IndexedValue<BinaryOutputStatus, uint16_t>> staticControlStatii;

		std::vector<IndexedValue<Counter, uint16_t>> eventCounters;
		std::vector<IndexedValue<Counter, uint16_t>> staticCounters;

		std::vector<IndexedValue<Analog, uint16_t>> eventAnalogs;
		std::vector<IndexedValue<Analog, uint16_t>> staticAnalogs;

		std::vector<IndexedValue<AnalogOutputStatus, uint16_t>> staticSetpointStatii;

		std::vector<IndexedValue<ControlRelayOutputBlock, uint16_t>> crobRequests;

		std::vector<IndexedValue<AnalogOutputInt16, uint16_t>> aoInt16Requests;
		std::vector<IndexedValue<AnalogOutputInt32, uint16_t>> aoInt32Requests;
		std::vector<IndexedValue<AnalogOutputFloat32, uint16_t>> aoFloat32Requests;
		std::vector<IndexedValue<AnalogOutputDouble64, uint16_t>> aoDouble64Requests;

		std::vector<IndexedValue<OctetString, uint16_t>> indexPrefixedOctets;
		std::vector<IndexedValue<OctetString, uint16_t>> rangedOctets;
};

}

#endif
