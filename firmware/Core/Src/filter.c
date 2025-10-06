//
// Created by Степан on 02.10.2025.
//

#include "../Inc/filter.h"


float med_filter_tmp[MED_FIL_ITEM][MED_WIDTH_NUM ];
float med_filter_out[MED_FIL_ITEM];
uint8_t med_fil_cnt[MED_FIL_ITEM];

float Moving_Median(uint8_t item,uint8_t width_num,float in)
{
    uint8_t i,j;
    float t;
    float tmp[MED_WIDTH_NUM];

    if(width_num==0)
        return in;

    if(item >= MED_FIL_ITEM || width_num >= MED_WIDTH_NUM )
    {
        return 0;
    }
    else
    {
        if( ++med_fil_cnt[item] >= width_num )
        {
            med_fil_cnt[item] = 0;
        }

        med_filter_tmp[item][ med_fil_cnt[item] ] = in;

        for(i=0;i<width_num;i++)
        {
            tmp[i] = med_filter_tmp[item][i];
        }

        for(i=0;i<width_num-1;i++)
        {
            for(j=0;j<(width_num-1-i);j++)
            {
                if(tmp[j] > tmp[j+1])
                {
                    t = tmp[j];
                    tmp[j] = tmp[j+1];
                    tmp[j+1] = t;
                }
            }
        }
        return ( tmp[(uint16_t)width_num/2] );
    }
}
