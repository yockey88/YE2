using System;
using System.Runtime.CompilerServices;

namespace YE {

    public class ScriptTesting {

        ScriptTesting() {

            InternalCalls.LogTrace("<TestScript>::YE::ScriptTesting::ScriptOne()");

        }

        ~ScriptTesting() {

            InternalCalls.LogTrace("<TestScript>::YE::ScriptTesting::~ScriptOne()");

        }

        void Create() {

            InternalCalls.LogTrace("<TestScript>::YE::ScriptTesting::Create()"); // internal call to native function

        }

        void Update() {

            InternalCalls.LogTrace("<TestScript>::YE::ScriptTesting::Update()"); // internal call to native function

        }

        void Destroy() {

            InternalCalls.LogTrace("<TestScript>::YE::ScriptTesting::Destroy()"); // internal call to native function

        }

    }

}