namespace libak {
class MsgEnDecoder {
 public:
  virtual void encode_msg() = 0;
  virtual void decode_msg() = 0;
};
}  // namespace libak
