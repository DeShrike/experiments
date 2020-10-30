import functools
import shutil

import pytest

from unittest import mock

@functools.lru_cache(maxsize = 1)
def get_default_version() -> str:
    if shutil.which("nano"):
        return "system"
    else:
        return "default"

# @pytest.fixture(autouse = True)
def clear_lru_cahche():
   get_default_version.cache_clear()
   yield
   get_default_version.cache_clear()

@pytest.mark.usefixtures("clear_lru_cache")
def test_nano_does_not_exists():
    with mock.patch.object(shutil, "which", return_value = None):
        assert get_default_version() == "default"

@pytest.mark.usefixtures("clear_lru_cache")
def test_nano_exists():
    with mock.patch.object(shutil, "which", return_value = "/some/exe"):
        assert get_default_version() == "system"

def test_nano_exists_2():
    with mock.patch.object(shutil, "which", return_value = "/some/exe"):
        assert get_default_version.__wrapped__() == "system"
