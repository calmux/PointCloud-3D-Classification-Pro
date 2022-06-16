
/*
 * CV3BoostConverter.cpp
 *
 *  Created on: May 21, 2015
 *      Author: Gregory Kramida
 *   Copyright: 2015 Gregory Kramida
 */
#define NO_IMPORT_ARRAY
#define PY_ARRAY_UNIQUE_SYMBOL pbcvt_ARRAY_API

#include "pyboostcvconverter.hpp"
#if CV_VERSION_MAJOR >= 3

namespace pbcvt {

using namespace cv;
//===================   ERROR HANDLING     =========================================================

static int failmsg(const char *fmt, ...) {
	char str[1000];

	va_list ap;
	va_start(ap, fmt);
	vsnprintf(str, sizeof(str), fmt, ap);
	va_end(ap);

	PyErr_SetString(PyExc_TypeError, str);
	return 0;
}

static PyObject* failmsgp(const char *fmt, ...)
		{
	char str[1000];

	va_list ap;
	va_start(ap, fmt);
	vsnprintf(str, sizeof(str), fmt, ap);
	va_end(ap);

	PyErr_SetString(PyExc_TypeError, str);
	return 0;
}

//===================   THREADING     ==============================================================
class PyAllowThreads {
public:
	PyAllowThreads() :
			_state(PyEval_SaveThread()) {
	}
	~PyAllowThreads() {
		PyEval_RestoreThread(_state);
	}
private:
	PyThreadState* _state;
};

class PyEnsureGIL {
public:
	PyEnsureGIL() :
			_state(PyGILState_Ensure()) {
	}
	~PyEnsureGIL() {
		PyGILState_Release(_state);
	}
private:
	PyGILState_STATE _state;
};

enum {
	ARG_NONE = 0, ARG_MAT = 1, ARG_SCALAR = 2
};

class NumpyAllocator:
		public MatAllocator {
public:
	NumpyAllocator() {
		stdAllocator = Mat::getStdAllocator();
	}
	~NumpyAllocator() {
	}

	UMatData* allocate(PyObject* o, int dims, const int* sizes, int type,
			size_t* step) const {
		UMatData* u = new UMatData(this);
		u->data = u->origdata = (uchar*) PyArray_DATA((PyArrayObject*) o);
		npy_intp* _strides = PyArray_STRIDES((PyArrayObject*) o);
		for (int i = 0; i < dims - 1; i++)
			step[i] = (size_t) _strides[i];
		step[dims - 1] = CV_ELEM_SIZE(type);
		u->size = sizes[0] * step[0];
		u->userdata = o;
		return u;
	}

	UMatData* allocate(int dims0, const int* sizes, int type, void* data,
			size_t* step, int flags, UMatUsageFlags usageFlags) const {
		if (data != 0) {
			CV_Error(Error::StsAssert, "The data should normally be NULL!");
			// probably this is safe to do in such extreme case
			return stdAllocator->allocate(dims0, sizes, type, data, step, flags,
					usageFlags);
		}
		PyEnsureGIL gil;

		int depth = CV_MAT_DEPTH(type);
		int cn = CV_MAT_CN(type);
		const int f = (int) (sizeof(size_t) / 8);
		int typenum =
				depth == CV_8U ? NPY_UBYTE :
				depth == CV_8S ? NPY_BYTE :
				depth == CV_16U ? NPY_USHORT :
				depth == CV_16S ? NPY_SHORT :
				depth == CV_32S ? NPY_INT :
				depth == CV_32F ? NPY_FLOAT :
				depth == CV_64F ?
									NPY_DOUBLE :
									f * NPY_ULONGLONG + (f ^ 1) * NPY_UINT;
		int i, dims = dims0;
		cv::AutoBuffer<npy_intp> _sizes(dims + 1);
		for (i = 0; i < dims; i++)
			_sizes[i] = sizes[i];
		if (cn > 1)
			_sizes[dims++] = cn;
		PyObject* o = PyArray_SimpleNew(dims, _sizes, typenum);
		if (!o)
			CV_Error_(Error::StsError,
					("The numpy array of typenum=%d, ndims=%d can not be created", typenum, dims));
		return allocate(o, dims0, sizes, type, step);
	}

	bool allocate(UMatData* u, int accessFlags,
			UMatUsageFlags usageFlags) const {
		return stdAllocator->allocate(u, accessFlags, usageFlags);
	}

	void deallocate(UMatData* u) const {
		if (u) {
			PyEnsureGIL gil;