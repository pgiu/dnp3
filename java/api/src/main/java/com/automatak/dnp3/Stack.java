/**
 * Copyright 2013 Automatak, LLC
 *
 * Licensed to Automatak, LLC (www.automatak.com) under one or more
 * contributor license agreements. See the NOTICE file distributed with this
 * work for additional information regarding copyright ownership. Automatak, LLC
 * licenses this file to you under the Apache License Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0.html
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */
package com.automatak.dnp3;

/**
 * Represents a Outstation or Master. Can be shutdown and can have Virtual Terminal Object (VTO) endpoints bound to it.
 */
public interface Stack {

    /**
     * Permanently shutdown the stack. Calling shutdown() more than once or continuing to use any child objects
     * of the stack can cause a failure.
     */
    void shutdown();

    /**
     * Add a listener for changes to the stack state. All callbacks come from the thread pool.
     * An immediate callback will be made with the current state.
     * @param listener interface to call back with the state enumeration
     */
    void addStateListener(StackStateListener listener);

}
