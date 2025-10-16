class Sequential(Module):
  __parameters__ = []
  __buffers__ = []
  training : bool
  _is_full_backward_hook : Optional[bool]
  __annotations__["0"] = __torch__.torch.nn.modules.linear.___torch_mangle_12.Linear
  __annotations__["1"] = __torch__.torch.nn.modules.activation.___torch_mangle_13.ELU
  __annotations__["2"] = __torch__.torch.nn.modules.linear.___torch_mangle_14.Linear
  __annotations__["3"] = __torch__.torch.nn.modules.activation.___torch_mangle_15.ELU
  __annotations__["4"] = __torch__.torch.nn.modules.normalization.___torch_mangle_16.LayerNorm
  __annotations__["5"] = __torch__.torch.nn.modules.linear.___torch_mangle_17.Linear
