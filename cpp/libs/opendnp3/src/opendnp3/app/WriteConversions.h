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
#ifndef __WRITE_CONVERSIONS_H_
#define __WRITE_CONVERSIONS_H_

#include "opendnp3/app/MeasurementTypes.h"
#include "opendnp3/app/WriteConversionTemplates.h"

#include "opendnp3/objects/Group1.h"
#include "opendnp3/objects/Group2.h"
#include "opendnp3/objects/Group3.h"
#include "opendnp3/objects/Group4.h"
#include "opendnp3/objects/Group10.h"
#include "opendnp3/objects/Group11.h"
#include "opendnp3/objects/Group12.h"
#include "opendnp3/objects/Group20.h"
#include "opendnp3/objects/Group21.h"
#include "opendnp3/objects/Group22.h"
#include "opendnp3/objects/Group23.h"
#include "opendnp3/objects/Group30.h"
#include "opendnp3/objects/Group32.h"
#include "opendnp3/objects/Group40.h"
#include "opendnp3/objects/Group41.h"
#include "opendnp3/objects/Group42.h"

namespace opendnp3
{

// Group 1
typedef ConvertQ<Group1Var2, Binary> ConvertGroup1Var2;

// Group 2
typedef ConvertQ<Group2Var1, Binary> ConvertGroup2Var1;
typedef ConvertQT<Group2Var2, Binary> ConvertGroup2Var2;
typedef ConvertQTDowncast<Group2Var3, Binary, uint16_t> ConvertGroup2Var3;

// Group 3
typedef ConvertQ<Group3Var2, DoubleBitBinary> ConvertGroup3Var2;

// Group 3
typedef ConvertQ<Group4Var1, DoubleBitBinary> ConvertGroup4Var1;
typedef ConvertQT<Group4Var2, DoubleBitBinary> ConvertGroup4Var2;
typedef ConvertQTDowncast<Group4Var3, DoubleBitBinary, uint16_t> ConvertGroup4Var3;

// Group 10
typedef ConvertQ<Group10Var2, BinaryOutputStatus> ConvertGroup10Var2;

// Group 11
typedef ConvertQ<Group11Var1, BinaryOutputStatus> ConvertGroup11Var1;
typedef ConvertQT<Group11Var2, BinaryOutputStatus> ConvertGroup11Var2;

// Group 12
struct ConvertGroup12Var1 : private openpal::Uncopyable
{
	static Group12Var1 Apply(const ControlRelayOutputBlock& crob)
	{
		Group12Var1 ret;
		ret.code = crob.functionCode;
		ret.count = crob.count;
		ret.onTime = crob.onTimeMS;
		ret.offTime = crob.offTimeMS;
		ret.status = crob.status;
		return ret;
	}
};

// Group 20
typedef ConvertQV<Group20Var1, Counter> ConvertGroup20Var1;
typedef ConvertQVandTruncate<Group20Var2, Counter> ConvertGroup20Var2;

typedef ConvertV<Group20Var5, Counter> ConvertGroup20Var5;
typedef ConvertVandTruncate<Group20Var6, Counter> ConvertGroup20Var6;

// Group 21
typedef ConvertQV<Group21Var1, FrozenCounter> ConvertGroup21Var1;
typedef ConvertQVandTruncate<Group21Var2, FrozenCounter> ConvertGroup21Var2;

typedef ConvertQVT<Group21Var5, FrozenCounter> ConvertGroup21Var5;
typedef ConvertQVTandTruncate<Group21Var6, FrozenCounter> ConvertGroup21Var6;

typedef ConvertV<Group21Var9, FrozenCounter> ConvertGroup21Var9;
typedef ConvertVandTruncate<Group21Var10, FrozenCounter> ConvertGroup21Var10;

// Group 22
typedef ConvertQV<Group22Var1, Counter> ConvertGroup22Var1;
typedef ConvertQVandTruncate<Group22Var2, Counter> ConvertGroup22Var2;

typedef ConvertQVT<Group22Var5, Counter> ConvertGroup22Var5;
typedef ConvertQVTandTruncate<Group22Var6, Counter> ConvertGroup22Var6;

// Group 23
typedef ConvertQV<Group23Var1, FrozenCounter> ConvertGroup23Var1;
typedef ConvertQVandTruncate<Group23Var2, FrozenCounter> ConvertGroup23Var2;
typedef ConvertQVT<Group23Var5, FrozenCounter> ConvertGroup23Var5;
typedef ConvertQVTandTruncate<Group23Var6, FrozenCounter> ConvertGroup23Var6;

// Group 30
typedef ConvertQVRangeCheck<Group30Var1, Analog, AnalogQuality::AQ_OVERRANGE> ConvertGroup30Var1;
typedef ConvertQVRangeCheck<Group30Var2, Analog, AnalogQuality::AQ_OVERRANGE> ConvertGroup30Var2;
typedef ConvertVRangeCheck<Group30Var3, Analog> ConvertGroup30Var3;
typedef ConvertVRangeCheck<Group30Var4, Analog> ConvertGroup30Var4;
typedef ConvertQVRangeCheck<Group30Var5, Analog, AnalogQuality::AQ_OVERRANGE> ConvertGroup30Var5;
typedef ConvertQV<Group30Var6, Analog> ConvertGroup30Var6;

// Group 32
typedef ConvertQVRangeCheck<Group32Var1, Analog, AnalogQuality::AQ_OVERRANGE> ConvertGroup32Var1;
typedef ConvertQVRangeCheck<Group32Var2, Analog, AnalogQuality::AQ_OVERRANGE> ConvertGroup32Var2;
typedef ConvertQVTRangeCheck<Group32Var3, Analog, AnalogQuality::AQ_OVERRANGE> ConvertGroup32Var3;
typedef ConvertQVTRangeCheck<Group32Var4, Analog, AnalogQuality::AQ_OVERRANGE> ConvertGroup32Var4;
typedef ConvertQVRangeCheck<Group32Var5, Analog, AnalogQuality::AQ_OVERRANGE> ConvertGroup32Var5;
typedef ConvertQV<Group32Var6, Analog> ConvertGroup32Var6;
typedef ConvertQVTRangeCheck<Group32Var7, Analog, AnalogQuality::AQ_OVERRANGE> ConvertGroup32Var7;
typedef ConvertQVT<Group32Var8, Analog> ConvertGroup32Var8;

// Group 40 - TODO - strange to have no flag
typedef ConvertQVRangeCheck<Group40Var1, AnalogOutputStatus, 0> ConvertGroup40Var1;
typedef ConvertQVRangeCheck<Group40Var2, AnalogOutputStatus, 0> ConvertGroup40Var2;
typedef ConvertQVRangeCheck<Group40Var3, AnalogOutputStatus, 0> ConvertGroup40Var3;
typedef ConvertQV<Group40Var4, AnalogOutputStatus> ConvertGroup40Var4;

// Group 41
typedef ConvertQS<Group41Var1, AnalogOutputInt32> ConvertGroup41Var1;
typedef ConvertQS<Group41Var2, AnalogOutputInt16> ConvertGroup41Var2;
typedef ConvertQS<Group41Var3, AnalogOutputFloat32> ConvertGroup41Var3;
typedef ConvertQS<Group41Var4, AnalogOutputDouble64> ConvertGroup41Var4;

// Group 42
typedef ConvertQVRangeCheck<Group42Var1, AnalogOutputStatus, 0> ConvertGroup42Var1;
typedef ConvertQVRangeCheck<Group42Var2, AnalogOutputStatus, 0> ConvertGroup42Var2;
typedef ConvertQVTRangeCheck<Group42Var3, AnalogOutputStatus, 0> ConvertGroup42Var3;
typedef ConvertQVTRangeCheck<Group42Var4, AnalogOutputStatus, 0> ConvertGroup42Var4;
typedef ConvertQVRangeCheck<Group42Var5, AnalogOutputStatus, 0> ConvertGroup42Var5;
typedef ConvertQV<Group42Var6, AnalogOutputStatus> ConvertGroup42Var6;
typedef ConvertQVTRangeCheck<Group42Var7, AnalogOutputStatus, 0> ConvertGroup42Var7;
typedef ConvertQVT<Group42Var8, AnalogOutputStatus> ConvertGroup42Var8;

}

#endif
