# Put in const.py...
# from http://code.activestate.com/recipes/65207-constants-in-python
class _const:
    class ConstError(TypeError): pass  # Base exception class.
    class ConstCaseError(ConstError): pass

    def __setattr__(self, name, value):
        if name in self.__dict__:
            raise self.ConstError("Can't change const.%s" % name)
        if not name.isupper():
            raise self.ConstCaseError('const name %r is not all uppercase' % name)
        self.__dict__[name] = value

# Replace module entry in sys.modules[__name__] with instance of _const
# (and create additional reference to it to prevent its deletion -- see
#  https://stackoverflow.com/questions/5365562/why-is-the-value-of-name-changing-after-assignment-to-sys-modules-name)
import sys
_ref, sys.modules[__name__] = sys.modules[__name__], _const()

import const

const.X = 1
const.Y = 2
const.Z = 3


# NOTE: To use const in other modules
# import const
# print(const.X, const.Y, const.Z)


if __name__ == '__main__':
    import __main__  as const  # Test this module...

    try:
        const.Answer = 42  # Not OK to create mixed-case attribute name.
    except const.ConstCaseError as exc:
        print(exc)
    else:  # Test failed - no ConstCaseError exception generated.
        raise RuntimeError("Mixed-case const names should't be allowed!")

    try:
        const.ANSWER = 42  # Should be OK, all uppercase.
    except Exception as exc:
        raise RuntimeError("Defining a valid const attribute should be allowed!")
    else:  # Test succeeded - no exception generated.
        print('const.ANSWER set to %d raised no exception' % const.ANSWER)

    try:
        const.ANSWER = 17  # Not OK, attempt to change defined constant.
    except const.ConstError as exc:
        print(exc)
    else:  # Test failed - no ConstError exception generated.
        raise RuntimeError("Shouldn't be able to change const attribute!")