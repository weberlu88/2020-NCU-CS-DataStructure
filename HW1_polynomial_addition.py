# MIS Senior, Weber Lu.

def num(s):
    '''Convert string into int/float.'''
    try:
        return int(s)
    except ValueError:
        return round(float(s),1)

class Polynomial:

    CONST_ERROR_ADD = "adding error..."
    CONST_ERROR_PAR = "parsing error..."
    
    def __init__(self, coef, exp):
        '''一個多項式物件有2個field，int的指數 & int/float係數'''
        if int(coef) == coef:
            self.coef = int(coef)
        else:
            self.coef = float(coef)
        self.exp  = exp

    def __str__(self):
        if self.exp == 0:
            return "{}".format(self.coef) if (self.coef < 0) else "+{}".format(self.coef)
        elif self.coef == 1:
            return "+x^{}".format(self.exp)
        elif self.coef == -1:
            return "-x^{}".format(self.exp)
        return "{}x^{}".format(self.coef, self.exp) if (self.coef < 0) else "+{}x^{}".format(self.coef, self.exp)

    def __repr__(self):
        # return "Polynomial({}x^{})".format(self.coef, self.exp)
        # if positive than add '+' infront.
        if self.exp == 0:
            return "{}".format(self.coef) if (self.coef < 0) else "+{}".format(self.coef)
        elif self.coef == 1:
            return "+x^{}".format(self.exp)
        elif self.coef == -1:
            return "-x^{}".format(self.exp)
        return "{}x^{}".format(self.coef, self.exp) if (self.coef < 0) else "+{}x^{}".format(self.coef, self.exp)

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
        '''將題目的字串轉成list of Polynomial物件s'''

        def scanOperator(string):
            '''Find the index of '+' or '-'. Complexity = O(n).'''
            operator_idx = list()
            for i in range(len(string)):
                if string[i] == '-':
                    operator_idx.append({'idx': i, 'positive': False})
                elif string[i] == '+':
                    operator_idx.append({'idx': i, 'positive': True})
            return operator_idx

        def splitPolyStr(string, operator_idx) -> list:
            '''Divid huge string into list of substings. Ex:['+5.5x^5', '+3x^3', '+1']. Complexity = O(n).'''
            polystr_lst = list()
            for i, v in enumerate(operator_idx):
                if i != (len(operator_idx)-1):
                    begin = operator_idx[i]['idx']
                    end = operator_idx[i+1]['idx']
                    substr = string[begin:end]
                    polystr_lst.append(substr)
                else: # last operation
                    begin = operator_idx[i]['idx']
                    substr = string[begin:]
                    polystr_lst.append(substr)
            return polystr_lst

        # String must start with '+' or '-'.
        if string[0] != '-':
            string = "+"+string
        # print(string)

        # Divid origin full-string into a list of sub-string. # ['-2.6x^3', '+4.9']
        operator_idx = scanOperator(string)
        substr_lst = splitPolyStr(string, operator_idx)
        # print(operator_idx)
        # print(substr_lst)

        # Parse sub-stings into objects.
        lst = list()
        for i, v in enumerate(substr_lst): # v = '-2.6x^3' or '+1'
            # Positive / negative
            positive = True if v[0] == '+' else False
            v = v[1:]

            # 判斷指數係數
            coef, exp = 0, 0
            if v.find('x^') == -1:
                # v is 常數項(constant), expon is 0
                coef = num(v)
            else:
                # Expon not 0
                content = v.split('x^') #'x^1' > ['', '1'] #'2.6x^3' > ['2.6', '3'] 
                if len(content[0]):
                    # Coef not 1
                    exp  = num(content[1])
                    coef = num(content[0])
                else:
                    # Coef is 1
                    exp  = num(content[1])
                    coef = 1
                
            # Create Poly-obj & pushback in list
            if not positive:
                coef = (-coef)
            newpoly = Polynomial(coef, exp)
            lst.append(newpoly)
        return lst

def add2PolyList(a, b) -> list:
    '''A function that adds two polynomials(list like).'''
    lst = list()
    # When array a,b both not empty > looping.
    while( len(a)!=0 and len(b)!=0 ):
        res = Polynomial.compareExp(a[0], b[0])
        if res == 1: 
            # b.exp < a.exp
            ElemtoAttach = a[0]
            lst.append(Polynomial(ElemtoAttach.coef, ElemtoAttach.exp))
            del a[0]
            pass
        elif res == -1: 
            #  a.exp < b.exp
            ElemtoAttach = b[0]
            lst.append(Polynomial(ElemtoAttach.coef, ElemtoAttach.exp))
            del b[0]
            pass
        else: 
            # equal expon
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

def printPolyList(lst) -> None:
    '''Print the list in mathematical format as the ANSWER.'''
    first = True
    for i in lst:
        if first:
            first = False
            print(str(i)[1:], end='')
        else:
            print(i, end='')
    return

def main():
    # polyStr1 = input()
    # polyStr2 = input()
    # ex. 1
    # polyStr1 = "5x^5+3x^3+1"
    # polyStr2 = "4x^4+2x^2+x^1"
    # ex. 2
    # polyStr1 = "-4x^3+2.1"
    # polyStr2 = "-2.6x^3+4.9"
    # ex. 3
    polyStr1 = "3.7x^5-4.7x^2"
    polyStr2 = "5.7x^2-x^1+5"
    

    # print(polyStr1, polyStr2)
    a = Polynomial.parseString(polyStr1)
    b = Polynomial.parseString(polyStr2)
    # print(a)

    answer = add2PolyList(a, b)
    printPolyList(answer)

if __name__ == '__main__':
    main()