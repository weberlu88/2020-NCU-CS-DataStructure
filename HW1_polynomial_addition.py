class Polynomial:

    CONST_ERROR_ADD = "adding error..."
    CONST_ERROR_PAR = "parsing error..."
    
    def __init__(self, coef, exp):
        '''一個多項式物件有2個field，int的指數&係數'''
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
    def compareExp(cls, poly1, poly2):
        '''比較次數，if前項次數大return 1'''
        if poly1.exp > poly2.exp:
            return 1
        elif poly1.exp < poly2.exp:
            return -1
        return 0

    @classmethod
    def add(cls, poly1, poly2):
        if poly1.exp == poly2.exp:
            return Polynomial(poly1.coef+poly2.coef, poly1.exp)
        else:
            print(cls.CONST_ERROR_ADD)
            return False

    @classmethod
    def parseString(cls, string) -> list:
        '''將題目的字串轉成Polynomial物件，目前只能處理+號，-號會被當+號'''
        # import re
        lst = list()
        for p in string.split('+'): # p = 5x^5
            coef, exp = 0, 0
            # 判斷指數係數
            content = p.split('x^')
            if len(content) == 1: # 零次式 
                exp  = 0
                coef = int(content[0])
            elif len(content) == 2: # N次式
                if content[0] is None: # 係數 = 1
                    exp  = int(content[1])
                    coef = 1
                else: # 係數 != 1
                    exp  = int(content[1])
                    coef = content[0]  #<<<<<<<<<< Has a bug!!!!!!!!!!!!!!!!!!!
            else:
                print(cls.CONST_ERROR_PAR)
            newpoly = Polynomial(coef, exp)
            lst.append(newpoly)
        return lst

def add2PloyList(a, b):
    '''A function that adds two polynomials(list like).'''
    lst = list()
    # When array a,b both not empty > looping.
    while( len(a)!=0 and len(b)!=0 ):
        res = Polynomial.compareExp(a[0], b[0])
        if res == 1: # b.exp < a.exp
            ElemtoAttach = a[0]
            lst.append(Polynomial(ElemtoAttach.coef, ElemtoAttach.exp))
            del a[0]
            pass
        elif res == -1: #  a.exp < b.exp
            ElemtoAttach = b[0]
            lst.append(Polynomial(ElemtoAttach.coef, ElemtoAttach.exp))
            del b[0]
            pass
        else: # equal expon
            coefficient = a[0].coef + b[0].coef
            if coefficient != 0:
                lst.append(Polynomial(coefficient, a[0].exp))
            del a[0]
            del b[0]
            pass
    # Exit loop when one of array is empty.
    if len(a)!=0:
        lst.extend(a)
    if len(b)!=0:
        lst.extend(b)
    return lst

def main():
    # polyStr1 = input()
    # polyStr2 = input()
    polyStr1 = "5x^5+3x^3+1"
    polyStr2 = "4x^4+2x^2+x^1"

    # print(polyStr1, polyStr2)
    # a = Polynomial.parseString(polyStr1)
    # b = Polynomial.parseString(polyStr2)
    # print(a)

    # answer = add2PloyList(a, b)
    # print(str(answer))

if __name__ == '__main__':
    # print("+1".split('+'))
    main()
    poly = Polynomial.parseString('x^0')
    print('指數', type(poly[0].exp), poly[0].exp)
    print('係數', type(poly[0].coef), poly[0].coef)