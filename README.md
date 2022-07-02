# projet_blockchain_python

Here we will generate private and public keys, that we'll use them to create signature, and then check the validation

1) Use
- cd projet_blockchain_python
- git submodule init
- git submodule update

- cd Signature_component
- make
- python3

```
import composant_cle
import Signature_component
from hashlib import sha256

cle=composant_cle.Cle()
sign=Signature_component.Signature()

cle.initialize("4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0")
Private_key=cle.getPrivateKey()
Public_key=cle.getPublicKey()

message=b"hello"
hash=sha256(message)
hm=hash.hexdigest()
MySignature=sign.Message_Signature(hm, Private_key)
Validate=sign.Signature_validation(hm, Public_key, MySignature)
Validate

```


Realised by Samar Rhilane – Luiz Motta Marchesini – Taoufik Haitam
