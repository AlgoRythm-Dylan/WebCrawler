#include "PrintInteractiveCommand.h"

#include <PrettyPrinting.h>

#include "InteractiveCrawl.h"

void PrintInteractiveCommand::execute()
{
	auto programPtr = program.lock();

	pretty_print_document(programPtr->current_job->document);
}