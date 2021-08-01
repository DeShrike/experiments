#include <stdio.h>
#include <yaml.h>

int led1 = 0;
int led2 = 0;
int led3 = 0;
int led4 = 0;
int fan = 0;
int button1 = 0;
int button2 = 0;

void do_indent(int count)
{
    int i;
    for (i = 0; i <= count; i++)
    {
        printf("  ");
    }
}

int read_config(void)
{
    FILE *fh = fopen("yamltest.yaml", "r");
    yaml_parser_t parser;
    yaml_token_t  token;

    /* Initialize parser */
    if (!yaml_parser_initialize(&parser))
    {
        fputs("Failed to initialize parser!\n", stderr);
    }

    if (fh == NULL)
    {
        fputs("Failed to open file!\n", stderr);
    }

    /* Set input file */
    yaml_parser_set_input_file(&parser, fh);

    char* last_key = (char*)malloc(1000);
    char* last_value = (char*)malloc(1000);
    int next_is_key = 0;
    int next_is_value = 0;
    // int in_pins = 0;
    // int in_actions = 0;

    int indent = 0;
    do
    {
        yaml_parser_scan(&parser, &token);
        // printf("Token Type %d ", token.type);
        switch (token.type)
        {
            case YAML_STREAM_START_TOKEN:
                // printf("STREAM START\n");
                break;
            case YAML_STREAM_END_TOKEN:
                // printf("STREAM END\n");
                break;
            case YAML_KEY_TOKEN:
                do_indent(indent);
                printf("(Key token)   ");
                next_is_key = 1;
                break;
            case YAML_VALUE_TOKEN:
                do_indent(indent);
                printf("(Value token) ");
                next_is_value = 1;
                break;
            case YAML_BLOCK_SEQUENCE_START_TOKEN:
                do_indent(indent);
                printf("{\n");
                // printf("\nStart Block (Sequence)\n");
                indent++;
                break;
            case YAML_BLOCK_ENTRY_TOKEN:
                // do_indent(indent);
                // printf("Start Block (Entry)\n");
                // printf("[\n");
                indent++;
                break;
            case YAML_BLOCK_END_TOKEN:
                indent--;
                do_indent(indent);
                // printf("End block\n");
                printf("]\n");
                break;
            case YAML_BLOCK_MAPPING_START_TOKEN:
                printf("\n");
                do_indent(indent);
                printf("[Block mapping]\n");
                break;
            case YAML_TAG_TOKEN:
                // printf("tag '%s %s' \n", token.data.tag.handle, token.data.tag.suffix);
                break;
            case YAML_SCALAR_TOKEN:
                printf("scalar '%s' \n", token.data.scalar.value);
                if (next_is_key)
                {
                	strcpy(last_key, (char*)token.data.scalar.value);
                	next_is_key = 0;
                }
                else if (next_is_value)
                {
                	strcpy(last_value, (char*)token.data.scalar.value);
                	next_is_value = 0;
                }

                break;
            default:
                printf("Got unknown token: %d\n", token.type);
                break;
        }

        if (token.type != YAML_STREAM_END_TOKEN)
        {
            yaml_token_delete(&token);
        }
    } while (token.type != YAML_STREAM_END_TOKEN);

    yaml_token_delete(&token);

    /* Cleanup */
    yaml_parser_delete(&parser);
    fclose(fh);

    free(last_key);
    free(last_value);

    return 0;
}

int main()
{
	read_config();
}
