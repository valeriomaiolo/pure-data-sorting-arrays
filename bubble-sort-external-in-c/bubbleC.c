//
//  bubble.c
//  Bubble
//
//  Created by Valerio Maiolo on 24/09/2021.
//

#include "m_pd.h"
#include <math.h>

static t_class *bubbleC_class;

typedef struct _bubbleC
{
    t_object x_obj;
    //t_float in;
    
    //t_outlet *out;
    
} t_bubbleC;

void bubbleC_bang(t_bubbleC *x)
{
  outlet_bang(x->x_obj.ob_outlet);
}

void bubbleC_float(t_bubbleC *x, t_floatarg f){
    outlet_float(x->x_obj.ob_outlet, f);
}

void bubbleC_list(t_bubbleC *x, t_symbol *s, int argc, t_atom *argv){
    
    int length = argc;
    int temp = 0;
    float arr[length];
    
    for(int i = 0; i < length; i++)
    {
        arr[i] = atom_getfloat(argv + i);
    }
    
    
    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < length - 1; j++)
        {
           if(arr[j] > arr[j+1])
           {
            temp = arr[j];
            arr[j]=arr[j+1];
            arr[j+1]=temp;
            }
        }
    }
    for(int i = 0; i < length; i++){
        SETFLOAT(argv+i, arr[i]);
    }
    outlet_list(x->x_obj.ob_outlet, &s_list, argc, argv);
}



void *bubbleC_new(t_symbol *s, int argc, t_atom *argv)
{
    t_bubbleC *x = (t_bubbleC *)pd_new(bubbleC_class);
    
    outlet_new(&x->x_obj, &s_list);
    
    return (void *)x;
}

void bubbleC_setup(void)
{
    bubbleC_class = class_new(gensym("bubbleC"),
                              (t_newmethod)bubbleC_new,
                              0, sizeof(t_bubbleC),
                              CLASS_DEFAULT,
                              A_GIMME, 0);
    
    class_addbang(bubbleC_class, bubbleC_bang);
    class_addlist(bubbleC_class, bubbleC_list);
    class_sethelpsymbol(bubbleC_class, gensym("bubbleC"));
}
