#ifndef Math_H
#define Math_H

namespace kmath
{
	//Square root function, seems to provide higher speed than 
	//std math.h sqrt, and accuracy is good. Tested 
	float inline __declspec (naked) __fastcall sqrt(double n)
	{
		_asm fld qword ptr [esp+4]
		_asm fsqrt
		_asm ret 8
	}	

}

#endif // Math_H
