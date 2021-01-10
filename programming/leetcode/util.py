import json
from collections.abc import Iterable


class Runner:
    """
    The Runner is used to execute json format examples and get the outputs.
    """

    def __init__(self, env, data, verbose=False, preprocess=[], hooks=[]):
        self.env = env
        self.data = data
        self.verbose = verbose
        self.hooks = hooks
        self.preprocess = preprocess
        self.class_instance = None
        self.class_method_name = None

        self._setup()

    def _setup(self):
        assert isinstance(self.data, list), "Only support list data input!"
        if len(self.data) == 0:
            return

        if isinstance(self.data[0], str):
            """
            [
                '<case1>',
                '<case2>',
            ]
            """
            self.class_instance = self.env["Solution"]()
            for key in self.env["Solution"].__dict__.keys():
                if not key.startswith("_"):
                    self.class_method_name = key
                    break

            self.data = [json.loads(case) for case in self.data]

        elif isinstance(self.data[0], list):
            """
            [
                [
                    '[class_name, method1, method2, ...]',
                    '[class_param, method1_param, method2_param, ...]',
                ],
                [
                    '[class_name, method1, method2, ...]',
                    '[class_param, method1_param, method2_param, ...]',
                ],
            ]
            """
            self.data = [[json.loads(i), json.loads(j)] for i, j in self.data]
        else:
            raise NotImplementedError("Not support such data input yet: {}".format(self.data))

    def exec(self):
        if self.class_instance and self.class_method_name:
            outputs = []
            for case_index, data in enumerate(self.data, start=1):
                if self.verbose:
                    print(" Case {} ".format(case_index).center(80, "#"))

                for pre in self.preprocess:
                    pre_func = self._get_func(pre)
                    data = pre_func(data)

                res = self.exec_step(self.class_method_name, data)
                outputs.append(res)

                self.exec_hooks()

                if self.verbose:
                    print()

        else:
            outputs = []
            for case_index, (methods, params) in enumerate(self.data, start=1):
                if self.verbose:
                    print(" Case {} ".format(case_index).center(80, "#"))

                output = []
                class_name = methods[0]
                class_param = params[0]
                self.class_instance = self.env[class_name](*tuple(class_param))
                for i, (method, param) in enumerate(zip(methods[1:], params[1:]), start=1):
                    res = self.exec_step(method, param, i)
                    self.exec_hooks()
                    output.append(res)

                if self.verbose:
                    print()

                outputs.append(output)

        return outputs

    def exec_step(self, method, param, i=1):
        func = self._get_func(method)
        if isinstance(param, Iterable):
            param = tuple(param)
        else:
            param = tuple([param])
        res = func(*param)
        if self.verbose:
            print("In [{}]: obj.{}{}".format(i, method, param))
            print("Out [{}]: {}".format(i, res))
        return res

    def exec_hooks(self):
        for hook in self.hooks:
            if isinstance(hook, str):
                if self.verbose:
                    print("  (hook {}): ".format(hook), end=" ")
                func = self._get_func(hook)
                func()
            elif isinstance(hook, dict):
                assert self.hooks.keys() == 1
                if self.verbose:
                    print("  (hook {}): ".format(hook.keys()[0]), end=" ")
                func = self._get_func(hook.keys()[0])
                func(*tuple(hook.values()))
            else:
                raise NotImplementedError("Not implemented hook {}".format(hook))

    def _get_func(self, name, obj=None):
        if obj is not None:
            return getattr(obj, name)
        else:
            if hasattr(self.class_instance, name):
                return getattr(self.class_instance, name)
            elif name in self.env.keys():
                return self.env[name]
            else:
                raise ValueError("Not found func with name {}".format(name))
