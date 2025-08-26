from setuptools import find_packages
from setuptools import setup

setup(
    name='hardware_msg',
    version='0.0.0',
    packages=find_packages(
        include=('hardware_msg', 'hardware_msg.*')),
)
