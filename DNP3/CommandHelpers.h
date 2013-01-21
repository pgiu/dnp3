
//
// Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
// more contributor license agreements. See the NOTICE file distributed
// with this work for additional information regarding copyright ownership.
// Green Energy Corp licenses this file to you under the Apache License,
// Version 2.0 (the "License"); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// This file was forked on 01/01/2013 by Automatak, LLC and modifications
// have been made to this file. Automatak, LLC licenses these modifications to
// you under the GNU Affero General Public License Version 3.0
// (the "Additional License"). You may not use these modifications except in
// compliance with the additional license. You may obtain a copy of the Additional
// License at
//
// http://www.gnu.org/licenses/agpl.html
//
// Contact Automatak, LLC for a commercial license to these modifications
//

#ifndef __COMMAND_HELPERS_H_
#define __COMMAND_HELPERS_H_

#include "APDUConstants.h"
#include "APDU.h"
#include "ObjectInterfaces.h"
#include "ObjectReadIterator.h"

#include <APL/CommandTypes.h>

#include <functional>

namespace apl
{
namespace dnp
{

// Static helper functions for formatting/validating command requests
class CommandHelpers
{
	public:
		template <class T>
		static std::function<CommandStatus (const APDU&)> ConfigureRequest(APDU& arAPDU, FunctionCodes aCode, const T& arCommand, size_t aIndex, CommandObject<T>* apObj);

		static CommandObject<Setpoint>* GetOptimalEncoder(SetpointEncodingType aType)		
		{
			switch(aType) {
			case SPET_INT16: return Group41Var2::Inst();
			case SPET_INT32: return Group41Var1::Inst();
			case SPET_FLOAT: return Group41Var3::Inst();
			case SPET_DOUBLE: return Group41Var4::Inst();
			default:
				throw ArgumentException(LOCATION, "Enum not handled");
			}
		}
	
	private:
		template <class T>
		static CommandStatus ValidateCommandResponse(const APDU& arAPDU, CommandObject<T>* apObj, const CopyableBuffer& arData, size_t aIndex);	
};

template <class T>
std::function<CommandStatus (const APDU&)> CommandHelpers::ConfigureRequest(APDU& arAPDU, FunctionCodes aCode, const T& arCommand, size_t aIndex, CommandObject<T>* apObj)
{	
	arAPDU.Set(aCode, true, true, false, false);
	IndexedWriteIterator i = arAPDU.WriteIndexed(apObj, 1, aIndex);
	i.SetIndex(aIndex);
	apObj->Write(*i, arCommand);
	CopyableBuffer buffer = apObj->GetValueBytes(*i);
	return [=](const APDU& arResponse){
		return CommandHelpers::ValidateCommandResponse(arResponse, apObj, buffer, aIndex);
	};	
}

template <class T>
CommandStatus CommandHelpers::ValidateCommandResponse(const APDU& arAPDU, CommandObject<T>* apObj, const CopyableBuffer& arData, size_t aIndex)
{
	HeaderReadIterator hdr = arAPDU.BeginRead();
	if(hdr.Count() == 1) {

		int grp = hdr->GetGroup();
		int var = hdr->GetVariation();

		if(grp == apObj->GetGroup() && var == apObj->GetVariation()) {
			ObjectReadIterator obj = hdr.BeginRead();
			if(obj.Count() == 1 && obj->Index() == aIndex) { //compare what was written to what was received
				T cmd = apObj->Read(*obj);
				if(arData == apObj->GetValueBytes(*obj)) return cmd.mStatus;
				else return CS_FORMAT_ERROR;
			}
		}
	}

	return CS_UNDEFINED;
}

}
}

#endif
