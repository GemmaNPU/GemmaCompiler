extern "C" 
{
    /**
     * Assemble a single line into a human hex string
     */
    const char* assemble_line(char *instructions);

    /**
     * Resturn a string with an error if the last instruction assemble got an error, an empty string if no errors
     */
    const char* error();
}