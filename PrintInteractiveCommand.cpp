#include "PrintInteractiveCommand.h"

#include <PrettyPrinting.h>

#include "InteractiveCrawl.h"

void PrintInteractiveCommand::execute()
{
	pretty_print_document(program->current_job->document);
}