#ifndef CLASSES_H
#define CLASSES_H

enum NodeType
{
    nt_base,
    nt_instance,
    nt_struct,
    nt_hidden,
    nt_hex32,
    nt_hex64,
    nt_hex16,
    nt_hex8,
    nt_pointer,
    nt_int64,
    nt_int32,
    nt_int16,
    nt_int8,
    nt_float,
    nt_double,
    nt_uint32,
    nt_uint16,
    nt_uint8,
    nt_text,
    nt_unicode,
    nt_function,
    nt_custom,
    nt_vec2,
    nt_vec3,
    nt_quat,
    nt_matrix,
    nt_vtable,
    nt_array,
    nt_class,
    nt_enum,
    nt_pchar
};

#endif // CLASSES_H
