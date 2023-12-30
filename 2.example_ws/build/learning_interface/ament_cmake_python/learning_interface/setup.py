from setuptools import find_packages
from setuptools import setup

setup(
    name='learning_interface',
    version='0.0.0',
    packages=find_packages(
        include=('learning_interface', 'learning_interface.*')),
)
