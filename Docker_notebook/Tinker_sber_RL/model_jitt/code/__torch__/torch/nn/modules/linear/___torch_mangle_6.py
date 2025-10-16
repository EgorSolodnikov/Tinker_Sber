class Linear(Module):
  __parameters__ = ["weight", "bias", ]
  __buffers__ = []
  weight : Tensor
  bias : Tensor
  training : bool
  _is_full_backward_hook : Optional[bool]
  def forward(self: __torch__.torch.nn.modules.linear.___torch_mangle_6.Linear,
    input: Tensor) -> Tensor:
    _0 = self.bias
    input0 = torch.linear(input, self.weight, _0)
    return input0
