using System;
using System.Runtime.CompilerServices;

namespace YE {

    internal static class InternalCalls {

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal static extern void LogInfo(string message);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal static extern void LogTrace(string message);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal static extern void LogDebug(string message);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal static extern void LogWarning(string message);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal static extern void LogError(string message);

    }

}