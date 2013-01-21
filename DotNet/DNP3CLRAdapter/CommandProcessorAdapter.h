
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
#ifndef __COMMAND_PROCESSOR_ADAPTER_H_
#define __COMMAND_PROCESSOR_ADAPTER_H_

using namespace System::Collections::ObjectModel;

#include <vcclr.h>
#include <map>

#include <DNP3/ICommandProcessor.h>

using namespace DNP3::Interface;

namespace DNP3
{		
namespace Adapter
{	
	public class ResponseRouter
	{
		public:			
			static void Set(gcroot<Future<CommandStatus>^>* apFuture, apl::CommandResponse cr);		
	};

	public ref class CommandProcessorAdapter : public ICommandProcessor
	{		
		public:

		CommandProcessorAdapter(apl::dnp::ICommandProcessor* apProxy);		

		virtual IFuture<CommandStatus>^ Select(BinaryOutput^ command, System::UInt32 index);
        virtual IFuture<CommandStatus>^ Select(Setpoint^ command, System::UInt32 index);
		virtual IFuture<CommandStatus>^ Operate(BinaryOutput^ command, System::UInt32 index);
        virtual IFuture<CommandStatus>^ Operate(Setpoint^ command, System::UInt32 index);

		private:

		apl::dnp::ICommandProcessor* mpProxy;		
	};
	
}}

#endif
