class Linear(Module):
  __parameters__ = ["weight", "bias", ]
  __buffers__ = []
  weight : Tensor
  bias : Tensor
  training : bool
  _is_full_backward_hook : Optional[bool]
  def forward(self: __torch__.torch.nn.modules.linear.___torch_mangle_10.Linear,
    argument_1: Tensor) -> Tensor:
    _0 = self.bias
    input = torch.linear(argument_1, self.weight, _0)
    return input
