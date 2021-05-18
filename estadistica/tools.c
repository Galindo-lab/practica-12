

void read_data(char filename[], Array *data)
{
    char ch;
    FILE *fp = fopen(filename, "r");
    int i = 0;
    float foo = 0, decimal = 0;

    while((ch = fgetc(fp)) != EOF)
    {
        if(ch != '\n')
        {
            switch(ch)
            {
                case '.':
                    decimal = 1;
                    break;
                default:

                    if(decimal != 0)
                    {
                        decimal *= 10;
                        foo += (float)(ch - '0')/decimal;
                    }
                    else
                    {
                        foo = foo*10 + (float)(ch - '0') ;
                    }

                    break;
            }

        }
        else
        {
            insertArray(data, foo);
            foo = 0;
            decimal = 0;
            i++;
        }
    }

    fclose(fp);
}
