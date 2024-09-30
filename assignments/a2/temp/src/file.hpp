/*
 * Description: SimpleDraw file operation function header
 * Author: HBF
 * Version: 2021-08-24
 */

#ifndef FILE_HPP_
#define FILE_HPP_

#include "object.hpp"

int saveSVG(const char *filename, int winWidth, int  winHeight);
int openSVG(const char *filename);
int saveBitmap(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight);

#endif /* FILE_HPP_ */
