from sys import setdlopenflags
from ctypes import RTLD_GLOBAL
setdlopenflags (RTLD_GLOBAL | 2)

from sys import setdlopenflags
from ctypes import RTLD_GLOBAL
setdlopenflags(RTLD_GLOBAL | 2)

#  Signature_component.so and composant_cle.so in  ./ folder 

import composant_cle
import Signature_component

cle = composant_cle.Cle()
sign = Signature_component.Signature()


init = cle.initialize("4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0")# test initialize for diff key
Private_key = cle.getPrivateKey()
Public_key = cle.getPublicKey()

message = "hello"



def CreateSignatur(message, Private_key) :
	MySignature = sign.Message_Signature(message, Private_key)
	return MySignature

def VerifySignature(message, Public_key):
	MySignature = CreateSignatur(message, Private_key)
	Validate = sign.Signature_validation(message, Public_key, MySignature)
	return Validate

def VerifyLenSignature(Signature):
	if((len(Signature) < 30) | (len(Signature)==0)):
		print("Signature Length is not valid")
	print("Signature Length is valid")

def VerifyEmptySignature(Signature):
	if(SIgnature==""):
		print("Signature is Empty")


def VerifyEmptySignature(message) :
	if (message == "") :
		print("Message is Empty")



		
Signature = sign.Message_Signature(message, Private_key)

CreateSignatur(message, Private_key)
VerifySignature(message, Public_key)
VerifyLenSignature(Signature)
VerifyEmptySignature(Signature)
VerifyEmptySignature(message)
