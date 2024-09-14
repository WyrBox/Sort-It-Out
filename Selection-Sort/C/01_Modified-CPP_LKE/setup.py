from setuptools import setup, Extension
from Cython.Build import cythonize

extensions = [
    Extension(
        name="mymodule",  # Name of the generated module
        sources=["mymodule.pyx", "Sort_LKE.c"],  # Include the Cython and C source files
        include_dirs=[],  # Add paths to any include files if needed
        extra_compile_args=["-O3"],  # Optimization flags, optional
        language="c",  # Specify that this is C code
    )
]

setup(ext_modules=cythonize(extensions))