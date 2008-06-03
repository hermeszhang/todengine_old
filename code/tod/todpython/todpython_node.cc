#include "tod/todpython/todpython_extension.h"

#include "tod/core/typeid.h"

using namespace tod;

//-----------------------------------------------------------------------------
PyObject* TodNode_new(PyTypeObject* type, PyObject* args, PyObject* keys)
{
    TodNode* o = reinterpret_cast<TodNode*>(type->tp_alloc(type, 0));
    return reinterpret_cast<PyObject*>(o);
}


//-----------------------------------------------------------------------------
void TodNode_dealloc(PyObject* self)
{
    TodNode* o = reinterpret_cast<TodNode*>(self);
    if (o->node_.valid())
        g_todobjects.erase(o->node_->getAbsolutePath());
    o->node_.release();
    self->ob_type->tp_free(self);
}


//-----------------------------------------------------------------------------
PyObject* TodNode_repr(TodNode* self)
{
    return PyString_FromString((*self->node_)->
        getAbsolutePath().toAnsiString().c_str());
}


//-----------------------------------------------------------------------------
PyObject* TodNode_getattro(TodNode* self, PyObject* name)
{
    self->attrName_ = name;
    Py_INCREF(self);
    Py_INCREF(name);
    return (PyObject*)(self);
}


//-----------------------------------------------------------------------------
PyObject* TodNode_call(PyObject* self, PyObject* args, PyObject* keys)
{
    TodNode* o = reinterpret_cast<TodNode*>(self);
    if (o->node_.invalid())
        return PyErr_Format(PyExc_Exception, "invalid TodNode");
    return invoke_method(
        o->node_, o->attrName_, o->node_->getAbsolutePath(), args, keys);
}


//-----------------------------------------------------------------------------
int TodNode_setattro(TodNode* self, PyObject* name, PyObject* value)
{
    if (self->node_.valid())
    {
        set_property(self->node_, self->node_->getAbsolutePath(), name, value);
    }
    return 0;
}

//-----------------------------------------------------------------------------
PyTypeObject TodNodeType =
{
    PyObject_HEAD_INIT(0)
    0,                                      // ob_size
    "TodNode",                              // tp_name
    sizeof(TodNode),                        // tp_basicssize
    0,                                      // tp_itemsize
    TodNode_dealloc,                        // tp_dealloc
    0,                                      // tp_print
    (getattrfunc)0,                         // tp_getattr
    (setattrfunc)0,                         // tp_setattr
    0,                                      // tp_compare
    0,                                      // tp_repr
    0,                                      // tp_as_number
    0,                                      // tp_as_mapping
    0,                                      // tp_as_sequence
    0,                                      // tp_as_hash
    (ternaryfunc)TodNode_call,              // tp_call
    (reprfunc)TodNode_repr,                 // tp_str
    (getattrofunc)TodNode_getattro,         // tp_getattro
    (setattrofunc)TodNode_setattro,         // tp_setattro
    0,                                      // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                     // tp_flags
    "TodPython Object",                     // tp_doc
    0,                                      // tp_traverse
    0,                                      // tp_clear
    0,                                      // tp_richcompare
    0,                                      // tp_weaklistoffset
    0,                                      // tp_iter
    0,                                      // tp_iternext
    0,                                      // tp_methods,
    0,                                      // tp_members
    0,                                      // tp_getset
    0,                                      // tp_base
    0,                                      // tp_dict
    0,                                      // tp_descr_get
    0,                                      // tp_descr_set
    0,                                      // tp_dictoffset
    0,                                      // tp_init
    0,                                      // tp_alloc
    TodNode_new,                          // tp_new
};
