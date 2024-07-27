import codewars_test as test

# Imagine you have a large project where is suddenly going something very messy. You are not able to guess what it is and don't want to debug all the code through. Your project has one base class.

# In this kata you will write metaclass Meta for your base class, which will collect data about all attribute accesses and method calls in all project classes. From this data you can then better guess what is happening or which method call is bottleneck of your app.

# We will use class Debugger to store the data. Method call collection should look like this:

# Debugger.method_calls.append({
#     'class': ..., # class object, not string
#     'method': ..., # method name, string
#     'args': args, # all args, including self
#     'kwargs': kwargs
# })
# Attribute access collection should look like this:

# Debugger.attribute_accesses.append({
#     'action': 'set', # set/get
#     'class': ..., # class object, not string
#     'attribute': ..., # name of attribute, string
#     'value': value # actual value
# })
# You should NOT log calls of getter/setter methods that you might create by meta class.

# See the tests if in doubts.



class Debugger(object):
    attribute_accesses = []
    method_calls = []

class DebugDescriptor:
    def __init__(self, name, value):
        self.name = name
        self.value = value

    def __get__(self, obj, objtype=None):
        if obj is not None:
            Debugger.attribute_access.append({
                'class': self,
                'attribute': self.name,
                'action': 'get',
                'value': self.value
            })
            print(f"Attribute accessed: {self.name}, Value: {self.value}")
        return self.value

    def __set__(self, obj, value):
        Debugger.attribute_access.append({
            'class': self,
            'attribute': self.name,
            'action': 'set',
            'value': value
        })
        print(f"Attribute modified: {self.name}, New value: {value}")
        self.value = value

class Meta(type):
    def __new__(cls, clsname, bases, attrs):
            def process_method_calls(key, value, self, *args, **kwargs):
                Debugger.method_calls.append(
                    {
                        'class': value, # class object, not string
                        'method': key, # method name, string
                        'args': (self,) + args, # all args, including self
                        'kwargs': kwargs
                    }
                )
                print(f"Method called: {key}, Args (including self): {(self,) + args}, Kwargs: {kwargs}")
            new_attrs = {}
            for key, value in list(attrs.items()):
                if callable(value) and key != '__new__':
                    def create_modified_method(original_method):
                        def modified_method(self, *args, **kwargs):
                            process_method_calls(key, value, self, *args, **kwargs)
                            return original_method(self, *args, **kwargs)
                        return modified_method
                    attrs[key] = create_modified_method(value)
                elif not key.startswith('__'):  # Skip special attributes
                    new_attrs[key] = DebugDescriptor(key, value)
                else:
                    new_attrs[key] = value
            
            return super().__new__(cls, clsname, bases, attrs)
        
    
class Foo(object, metaclass = Meta):
    def __init__(self, x):
        self.x = x

    def bar(self, v):
        return (self.x, v)
a = Foo(1)
a.bar(2)

calls = Debugger.method_calls

test.assert_equals(len(calls), 2)

test.describe("Test collected method calls")

test.it("Call to init should be collected")
test.assert_equals(calls[0]['args'], (a, 1))

test.it("Call to bar should be collected")
test.assert_equals(calls[1]['args'], (a, 2))

test.describe("Test collected attribute accesses")
accesses = Debugger.attribute_accesses

test.assert_equals(len(accesses), 3)

test.it("Attribute set in init should be collected")
test.assert_equals(accesses[0]['action'], 'set')
test.assert_equals(accesses[0]['attribute'], 'x')
test.assert_equals(accesses[0]['value'], 1)

test.it("Method get should be collected too")
test.assert_equals(accesses[1]['action'], 'get')
test.assert_equals(accesses[1]['attribute'], 'bar')

test.it("Attribute get should be collected")
test.assert_equals(accesses[2]['action'], 'get')
test.assert_equals(accesses[2]['attribute'], 'x')