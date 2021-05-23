from afirmatron import File


class TestAfirmatron:
    def test_get(self):
        bin = File.from_filename('a0:20:a6:27:0b:b2')

        assert bin.filename == 'a0:20:a6:27:0b:b2.bin'
        assert bin.md5 is not None
        assert bin.octet is not None
        assert bin.length is not None
        
