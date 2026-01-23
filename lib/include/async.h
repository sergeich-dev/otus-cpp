#ifndef _ASYNC_H_
#define _ASYNC_H_

#include "string_parser/string_parser.h"

std::unique_ptr<CStringParser> connect(size_t nBulkSize);

void receive(const char * buffer, size_t bufSize, const std::unique_ptr<CStringParser> & context) noexcept;

void disconnect(std::unique_ptr<CStringParser> & context);

#endif //_ASYNC_H_
