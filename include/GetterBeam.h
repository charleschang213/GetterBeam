/*****************************************************************************
 * @file     GetterBeam.h
 * @brief    Getter Beam CPU Interface
 * @author   Yichi Zhang
 * @date     2022/10/4
 *****************************************************************************/

#ifndef GETTERBEAM_GETTERBEAM_H
#define GETTERBEAM_GETTERBEAM_H

#include <string>

namespace GetterBeam
{
class GBCPU
{
public:
	static std::string HelloWorldText();
};
}	 // namespace GetterBeam

#endif	  // GETTERBEAM_GETTERBEAM_H
