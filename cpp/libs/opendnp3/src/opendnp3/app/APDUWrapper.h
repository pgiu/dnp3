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
#ifndef __APDU_WRAPPER__H_
#define __APDU_WRAPPER__H_

#include <openpal/container/ReadOnlyBuffer.h>
#include <openpal/container/WriteBuffer.h>

#include "opendnp3/gen/FunctionCode.h"
#include "opendnp3/app/AppControlField.h"
#include "opendnp3/app/ObjectWriter.h"

namespace opendnp3
{

enum class APDUEquality
{
	FULL_EQUALITY,
	OBJECT_HEADERS_EQUAL,
	NONE
};

// This class is used to write to an underlying buffer
class APDUWrapper
{
public:	

	APDUWrapper();

	APDUWrapper(const openpal::WriteBuffer& aBuffer);

	bool IsValid() const;

	void SetFunction(FunctionCode code);
	FunctionCode GetFunction() const;

	AppControlField GetControl() const;
	void SetControl(AppControlField control);

	uint32_t Size() const;

	openpal::ReadOnlyBuffer ToReadOnly() const;

	ObjectWriter GetWriter();

	uint32_t Remaining() const;

protected:

	static APDUEquality Compare(uint32_t headerSize, const openpal::ReadOnlyBuffer& lhs, const openpal::ReadOnlyBuffer& rhs);

	bool valid;
	openpal::WriteBuffer buffer;
	openpal::WriteBuffer remaining;
};

}

#endif
