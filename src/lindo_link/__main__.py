from .link import *

bd = BuildData()
if bd.platform == "Windows":
    windows(bd)
elif bd.platform == "Darwin":
    mac(bd)
else:
    linux(bd)