#
# The transformation orio.module.for generating a pragma directive
#

import sys
from orio.main.util.globals import *
import orio.module.module

#-----------------------------------------

class Pragma(orio.module.module.Module):
    '''Pragma transformation module.'''

    def __init__(self, perf_params, module_body_code, annot_body_code,
                 line_no, indent_size, language='C'):
        '''To instantiate a pragma transformation module.'''
        
        orio.module.module.Module.__init__(self, perf_params, module_body_code, annot_body_code,
                                      line_no, indent_size, language)

    #---------------------------------------------------------------------

    def __isNextNewlineChar(self, string):
        '''To determine if the next character is a newline (spaces are ignored)'''

        for c in string:
            if c == ' ':
                continue
            return (c == '\n')
        return False

    #---------------------------------------------------------------------
    
    def transform(self):
        '''To generate a pragma directive'''

        # evaluate the orio.module.body code to get the pragma string
        try:
            pragma_str = eval(self.module_body_code, self.perf_params)
        except Exception, e:
            err('orio.module.pragma.pragma:%s: failed to evaluate the Pragma orio.module.body code expression: "%s"\n --> %s: %s' %
                   (self.module_body_code,e.__class__.__name__, e))

        # generate the pragma directive if the pragma string is not empty
        pragma_directive = ''
        pragma_str = pragma_str.strip()
        if pragma_str:
            pragma_directive = '#pragma %s' % pragma_str
        
        # generate the transformed code
        transformed_code = ''
        transformed_code += '\n' + pragma_directive
        if not self.__isNextNewlineChar(self.annot_body_code):
            transformed_code += '\n'
        transformed_code += self.annot_body_code
        
        # return the transformed code
        return transformed_code

        