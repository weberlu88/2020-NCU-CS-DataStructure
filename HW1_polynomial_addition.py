class Polynomial:

    CONST_ERROR_ADD = "adding error..."
    CONST_ERROR_PAR = "parsing error..."
    
    def __init__(self, coef, exp):
        self.coef = coef
        self.exp  = exp

    def __str__(self):
        if self.exp == 0:
            return "{}".format(self.coef)
        return "{}x^{}".format(self.coef, self.exp)

    def __repr__(self):
        return "Polynomial({}x^{})".format(self.coef, self.exp)

    def hasSameExp(self, poly):
        if self.exp == poly.exp:
            return True
        return False

    @classmethod
    def add(cls, poly1, poly2):
        if poly1.exp == poly2.exp:
            return Polynomial(poly1.coef+poly2.coef, poly1.exp)
        else:
            print(cls.CONST_ERROR_ADD)
            return False

    @classmethod
    def parseString(cls, string) -> list:
        '''將題目的字串轉成Polynomial物件'''
        import re
        lst = list()
        for p in re.split('+',string): # p = 5x^5
            coef, exp = 0, 0
            # 判斷指數係數
            content = p.split('x^')
            if len(content) == 1: # 零次式
                exp  = 0
                coef = content[0]
            elif len(content) == 2: # N次式
                if content[0] is None: # 係數 = 1
                    exp  = content[1]
                    coef = 1
                else: # 係數 != 1
                    exp  = content[1]
                    coef = content[0]
            else:
                print(cls.CONST_ERROR_PAR)
            newpoly = Polynomial(coef, exp)
            lst.append(newpoly)
        return lst

def main():
    # polyStr1 = input()
    # polyStr2 = input()
    polyStr1 = "5x^5+3x^3+1"
    polyStr2 = "4x^4+2x^2+x^1"

    print(polyStr1, polyStr2)
    res = Polynomial.parseString(polyStr1)
    print(res)
  
if __name__ == '__main__':
    # print("+1".split('+'))
    main()