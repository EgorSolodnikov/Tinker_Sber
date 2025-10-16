class LayerNorm(Module):
  __parameters__ = ["weight", "bias", ]
  __buffers__ = []
  weight : Tensor
  bias : Tensor
  training : bool
  _is_full_backward_hook : Optional[bool]
  def forward(self: __torch__.torch.nn.modules.normalization.LayerNorm,
    argument_1: Tensor) -> Tensor:
    _0 = self.bias
    _1 = self.weight
    input = torch.layer_norm(argument_1, [256], _1, _0)
    return input
