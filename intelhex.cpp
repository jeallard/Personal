#include    "intelhex.h"
#include    <stdio.h>

int IntelHex::LoadFile(const char *fname)
{
    if(!InitForLoad())
        return 1;

    FILE *fp = fopen(fname,"rt");

    if(!fp)
        return 3;
    
    long    extended_addr=0;
    char    line[LINE_LEN];

    while(fgets(line,LINE_LEN,fp) != NULL)
    {
        if(line[0]!=':')
        {
            fclose(fp);
            return 4;   // Format error
        }

        long num_bytes = GetHexValue(line,1,2);
        long addr = GetHexValue(line,3,6);
        long type = GetHexValue(line,7,8);

        long checksum = num_bytes + type;

        // do checksum for address

        checksum += (addr>>8) & 0xff;
        checksum += addr&0xff;

        // Add the extended address to get the real address.

        addr += extended_addr;

        // check the record type

        if(type==0)
        {
            // Data record. Read in the data bytes.

            for(long k=0;k < num_bytes;k++)
            {
                int j = 9+k*2;
                
                long val = GetHexValue(line,j,j+1);
                checksum += val;

                // Store the byte in the proper block buffer.
                // If there's an error, return the error code.

                int ret_val = PutByte(addr,(uchar)val);
                if(ret_val)
                {
                    fclose(fp);
                    return ret_val;
                }

                addr++;
            }
 
        }
        else if(type==2 || type==4)
        {
            // Extended address

            if(num_bytes!=2)
            {
                fclose(fp);
                return 4;   // Format error
            }

            extended_addr = GetHexValue(line,9,12);

            checksum += (extended_addr>>8)&0xff;
            checksum += extended_addr&0xff;

            // Convert to linear extended address (if needed)

            if(type==2)
                extended_addr <<= 4;
			else
				extended_addr <<= 16;
        }
        else if(type==1)
        {
            fclose(fp);
            return 0;   // Success
        }

        // now get checksum and see if it matches.
        int j= 9+num_bytes*2;
        checksum += GetHexValue(line,j,j+1);
        if(checksum & 0xff)
        {
            fclose(fp);
            return 7;   // Checksum error
        }

    }

    fclose(fp);
    return 5;       // Premature end of file.
}



