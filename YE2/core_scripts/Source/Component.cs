using System;

namespace YE {

    public  abstract class Component {

        public Entity Entity { get; internal set; }

    }

    public class IDComponent : Component {

        // public string ID {

        //     // get => InternalCalls.ScriptID_GetID(this);
        //     // set => InternalCalls.ScriptID_SetID(this, value);

        // }

    }

}