#
# Contain the transformation procedure
#

import sys
import module.loop.ast

#-----------------------------------------

class Transformator:
    '''Code transformator'''

    def __init__(self, pragmas, stmt):
        '''To instantiate a code transformator object'''

        self.pragmas = pragmas
        self.stmt = stmt

        # remove all empty pragma strings
        self.pragmas = filter(lambda x: x.strip(), self.pragmas)

    #----------------------------------------------------------

    def transform(self):
        '''To insert pragma directives'''

        # no pragma directives insertions
        if len(self.pragmas) == 0:
            return self.stmt

        # create a pragma directive AST
        prags = [module.loop.ast.Pragma(p) for p in self.pragmas]

        # create the transformed statement
        if isinstance(self.stmt, module.loop.ast.CompStmt):
            stmts = self.stmt.stmts
        else:
            stmts = [self.stmt]
        transformed_stmt = module.loop.ast.CompStmt(prags + stmts)

        # return the transformed statement
        return transformed_stmt


