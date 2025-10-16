class Sequential(Module):
  __parameters__ = []
  __buffers__ = []
  training : bool
  _is_full_backward_hook : Optional[bool]
  __annotations__["0"] = __torch__.torch.nn.modules.linear.___torch_mangle_6.Linear
  __annotations__["1"] = __torch__.torch.nn.modules.activation.___torch_mangle_7.ELU
  __annotations__["2"] = __torch__.torch.nn.modules.linear.___torch_mangle_8.Linear
  __annotations__["3"] = __torch__.torch.nn.modules.activation.___torch_mangle_9.ELU
  __annotations__["4"] = __torch__.torch.nn.modules.linear.___torch_mangle_10.Linear
  def forward(self: __torch__.torch.nn.modules.container.___torch_mangle_11.Sequential,
    input: Tensor) -> Tensor:
    _0 = getattr(self, "4")
    _1 = getattr(self, "3")
    _2 = getattr(self, "2")
    _3 = getattr(self, "1")
    _4 = (getattr(self, "0")).forward(input, )
    _5 = (_1).forward((_2).forward((_3).forward(_4, ), ), )
    return (_0).forward(_5, )
