module Android where

import           System.IO (hSetBuffering, BufferMode (LineBuffering), stdout, stderr)

-- allow setting stdout to linebuffering if needed
foreign export ccall setLineBuffering :: IO ()
setLineBuffering :: IO ()
setLineBuffering = hSetBuffering stdout LineBuffering >> hSetBuffering stderr LineBuffering