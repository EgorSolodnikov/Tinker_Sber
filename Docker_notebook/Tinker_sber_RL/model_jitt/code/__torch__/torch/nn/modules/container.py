class Sequential(Module):
  __parameters__ = []
  __buffers__ = []
  training : bool
  _is_full_backward_hook : Optional[bool]
  __annotations__["0"] = __torch__.torch.nn.modules.linear.Linear
  __annotations__["1"] = __torch__.torch.nn.modules.activation.ELU
  __annotations__["2"] = __torch__.torch.nn.modules.linear.___torch_mangle_0.Linear
  __annotations__["3"] = __torch__.torch.nn.modules.activation.___torch_mangle_1.ELU
  __annotations__["4"] = __torch__.torch.nn.modules.normalization.LayerNorm
  __annotations__["5"] = __torch__.torch.nn.modules.linear.___torch_mangle_2.Linear
  __annotations__["6"] = __torch__.torch.nn.modules.activation.___torch_mangle_3.ELU
  __annotations__["7"] = __torch__.torch.nn.modules.normalization.___torch_mangle_4.LayerNorm
  __annotations__["8"] = __torch__.torch.nn.modules.linear.___torch_mangle_5.Linear
  def forward(self: __torch__.torch.nn.modules.container.Sequential,
    argument_1: __torch__.torch.nn.modules.activation.___torch_mangle_13.ELU,
    input: Tensor) -> Tensor:
    _0 = getattr(self, "8")
    _1 = getattr(self, "7")
    _2 = getattr(self, "5")
    _3 = getattr(self, "4")
    _4 = getattr(self, "2")
    _5 = (getattr(self, "0")).forward(input, )
    _6 = (_4).forward((argument_1).forward(_5, ), )
    _7 = (_3).forward((argument_1).forward1(_6, ), )
    _8 = (argument_1).forward2((_2).forward(_7, ), )
    return (_0).forward((_1).forward(_8, ), )
