/// \file WrapControl.h
/// \brief Definition of the WrapControl class

#ifndef tpkWRAPCONTROL_H
#define tpkWRAPCONTROL_H

#include "RotaryAxis.h"

namespace tpk {

/// Wrap Control
/**
    A Wrap Control object stores the wrap logic and position type codes for controlling
    a Rotary Axis object. The codes can have temporary values which revert to the
    permanent values when they are read.
*/
    class WrapControl {
        public:
            WrapControl() : mLogic(RotaryAxis::limit), mLogicTemp(mLogic),
                mReference(RotaryAxis::lastDemand), mReferenceTemp(mReference)
                {}
            WrapControl(
                RotaryAxis::wraplogic logic,            ///< logic code
                RotaryAxis::wrapref reference           ///< position reference
            ) : mLogic(logic), mLogicTemp(mLogic),
                mReference(reference), mReferenceTemp(mReference)
                {}
                
        /// Set values
            void set(
                RotaryAxis::wraplogic logic,            ///< logic code
                RotaryAxis::wrapref reference           ///< position reference
            ) {
                mLogic = logic;
                mLogicTemp = mLogic;
                mReference = reference;
                mReferenceTemp = mReference;
            }
            
        /// Set temporary values
            void setTemporary(
                RotaryAxis::wraplogic logic,            ///< logic code
                RotaryAxis::wrapref reference           ///< position reference
            ) {
                mLogicTemp = logic;
                mReferenceTemp = reference;
            }
            
        /// Get logic code
        /**
            \returns logic code
        */
            RotaryAxis::wraplogic getLogic() {
                RotaryAxis::wraplogic logic(mLogicTemp);
                mLogicTemp = mLogic;
                return logic;
            }
            
        /// Get reference position code
        /**
            \returns reference position code
        */
            RotaryAxis::wrapref getReference() {
                RotaryAxis::wrapref ref(mReferenceTemp);
                mReferenceTemp = mReference;
                return ref;
            }
            
        private:
            RotaryAxis::wraplogic mLogic; 
            RotaryAxis::wraplogic mLogicTemp; 
            RotaryAxis::wrapref mReference; 
            RotaryAxis::wrapref mReferenceTemp; 
    };
}
#endif
