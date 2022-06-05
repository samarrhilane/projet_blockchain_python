# projet_blockchain_python

Here we will generate private and public keys, that we'll use them to create signature, and then check the validation

1) Use
- cd Signature_component
- python3

```
import composant_cle
import Signature_component

cle=composant_cle.Cle()
sign=Signature_component.Signature()

cle.initialize("4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0")
Private_key=cle.getPrivateKey()
Public_key=cle.getPublicKey()

message="hello"
MySignature=sign.Message_Signature(message, Private_key)
Validate=sign.Signature_validation(message, Public_key, MySignature)
Validate

```


![valid sign](https://user-images.githubusercontent.com/29365707/172055837-8aaa2dc5-6feb-4511-926a-1f72cc9c990b.png)

Realised by Samar Rhilane – Luiz Motta Marchesini – Taoufik Haitam
