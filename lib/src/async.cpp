#include "async.h"

/**
* @brief Creates context for commands processing
*
* @param    nBulkSize                       Commands block size
* @return   std::unique_ptr<CStringParser>  Pointer to created context
*/
std::unique_ptr<CStringParser> connect(size_t nBulkSize)
{
    auto parser = std::make_unique<CStringParser>(nBulkSize);

    return parser;
}

/**
* @brief Receives command for processing and add to queue
*
* @param data       Command data buffer
* @param data_size  Command data buffer size
* @param context    Context for commands processing
*/
void receive(const char * buffer, size_t bufSize, const std::unique_ptr<CStringParser> & context) noexcept
{
    try
    {
        std::string buf(buffer, bufSize);

        context->ProcessString(buf);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

/**
* @brief Destroys context for commands processing
*
* @param context    Context for commands processing
*/
void disconnect(std::unique_ptr<CStringParser> & context)
{
    context.reset();
}
