#include <pybind11/pybind11.h>

#include "xchainer/array.h"

#include "xchainer/python/array.h"
#include "xchainer/python/device.h"
#include "xchainer/python/dtype.h"
#include "xchainer/python/error.h"
#include "xchainer/python/scalar.h"
#include "xchainer/python/shape.h"
#ifdef XCHAINER_ENABLE_CUDA
#include "xchainer/python/cuda/hello.h"
#endif  // XCHAINER_ENABLE_CUDA

namespace xchainer {

namespace py = pybind11;

namespace {

void InitXchainerModule(pybind11::module& m) {
    m.doc() = "xChainer";
    m.attr("__name__") = "xchainer";  // Show each member as "xchainer.*" instead of "xchainer.core.*"

    m.def("empty", &Array::Empty)
        .def("full", static_cast<Array (*)(const Shape&, Scalar, Dtype)>(&Array::Full))
        .def("full", static_cast<Array (*)(const Shape&, Scalar)>(&Array::Full))
        .def("zeros", &Array::Zeros)
        .def("ones", &Array::Ones)
        .def("empty_like", &Array::EmptyLike)
        .def("full_like", &Array::FullLike)
        .def("zeros_like", &Array::ZerosLike)
        .def("ones_like", &Array::OnesLike);
}
}  // namespace
}  // namespace xchainer

PYBIND11_MODULE(_core, m) {  // NOLINT
    xchainer::InitXchainerModule(m);
    xchainer::InitXchainerDevice(m);
    xchainer::InitXchainerDtype(m);
    xchainer::InitXchainerError(m);
    xchainer::InitXchainerScalar(m);
    xchainer::InitXchainerShape(m);
    xchainer::InitXchainerArray(m);
#ifdef XCHAINER_ENABLE_CUDA
    xchainer::cuda::InitXchainerCudaHello(m);
#endif  // XCHAINER_ENABLE_CUDA
}
