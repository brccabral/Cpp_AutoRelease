# AutoRelease

In C there is no classes with constructor/destructor, only `struct`, and libraries provide Create/Destroy, or
Load/Unload, or Begin/End functions.  
But many times I call Create but forget to call Destroy.   
Using class AutoRelease forces me to make sure I am calling the Destroy/Unload/End respective functions.  
Class code taken from https://www.youtube.com/watch?v=TwW9UPc8ImU&list=PLmm8GpQIMryC1Lm_YgphPgzwPue5RAZdi  
