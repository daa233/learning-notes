import json


class Runner:
    """
    The Runner is used to execute json format examples and get the outputs.
    """

    def __init__(self, methods, params):
        methods = json.loads(methods)
        params = json.loads(params)
        self.class_name = methods[0]
        self.class_param = params[0]
        self.methods = methods[1:]
        self.params = params[1:]

    def exec(self, env, verbose=False, hooks=[]):
        obj = env[self.class_name](*self.class_param)
        if verbose:
            print("Init: obj = {}{}".format(self.class_name, tuple(self.class_param)))
        outputs = []
        for i, (method, param) in enumerate(zip(self.methods, self.params)):
            func = getattr(obj, method)
            res = func(*param)
            if verbose:
                print("In [{}]: obj.{}{}".format(i, method, tuple(param)))
                print("Out [{}]: {}".format(i, res))
            if res:
                outputs.append(res)
            else:
                outputs.append("null")

            for hook in hooks:
                if isinstance(hook, str):
                    if verbose:
                        print("  (hook {}): ".format(hook), end=" ")
                    func = getattr(obj, hook)
                    func()
                elif isinstance(hook, dict):
                    assert hooks.keys() == 1
                    if verbose:
                        print("  (hook {}): ".format(hook.keys()[0]), end=" ")
                    func = getattr(obj, hook.keys()[0])
                    func(tuple(hook.values()))
                else:
                    raise NotImplementedError("Not implemented hook {}".format(hook))

            if verbose:
                print()

        return outputs
