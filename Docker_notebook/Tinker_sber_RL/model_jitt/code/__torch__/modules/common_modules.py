class MixedMlp(Module):
  __parameters__ = ["w0", "b0", "w1", "b1", "w2", "b2", ]
  __buffers__ = []
  w0 : Tensor
  b0 : Tensor
  w1 : Tensor
  b1 : Tensor
  w2 : Tensor
  b2 : Tensor
  training : bool
  _is_full_backward_hook : Optional[bool]
  gate : __torch__.torch.nn.modules.container.___torch_mangle_11.Sequential
  def forward(self: __torch__.modules.common_modules.MixedMlp,
    argument_1: Tensor,
    obs: Tensor) -> Tensor:
    _0 = self.b2
    _1 = self.w2
    _2 = self.b1
    _3 = self.w1
    _4 = self.b0
    _5 = self.w0
    _6 = self.gate
    input = torch.cat([argument_1, obs], 1)
    coefficients = torch.softmax((_6).forward(input, ), 1)
    flat_weight = torch.flatten(_5, 1, 2)
    _7 = torch.matmul(coefficients, flat_weight)
    _8 = ops.prim.NumToTensor(torch.size(coefficients, 0))
    _9 = int(_8)
    _10 = ops.prim.NumToTensor(torch.size(_5, 1))
    _11 = int(_10)
    _12 = ops.prim.NumToTensor(torch.size(_5, 2))
    mixed_weight = torch.view(_7, [_9, _11, int(_12)])
    input0 = torch.unsqueeze(torch.cat([argument_1, obs], 1), 1)
    mixed_bias = torch.unsqueeze(torch.matmul(coefficients, _4), 1)
    _13 = torch.baddbmm(mixed_bias, input0, mixed_weight)
    input1 = torch.squeeze(_13, 1)
    layer_out = torch.elu(input1, 1.)
    flat_weight0 = torch.flatten(_3, 1, 2)
    _14 = torch.matmul(coefficients, flat_weight0)
    _15 = ops.prim.NumToTensor(torch.size(coefficients, 0))
    _16 = int(_15)
    _17 = ops.prim.NumToTensor(torch.size(_3, 1))
    _18 = int(_17)
    _19 = ops.prim.NumToTensor(torch.size(_3, 2))
    mixed_weight0 = torch.view(_14, [_16, _18, int(_19)])
    _20 = torch.cat([argument_1, layer_out], 1)
    input2 = torch.unsqueeze(_20, 1)
    mixed_bias0 = torch.unsqueeze(torch.matmul(coefficients, _2), 1)
    _21 = torch.baddbmm(mixed_bias0, input2, mixed_weight0)
    input3 = torch.squeeze(_21, 1)
    layer_out0 = torch.elu(input3, 1.)
    flat_weight1 = torch.flatten(_1, 1, 2)
    _22 = torch.matmul(coefficients, flat_weight1)
    _23 = ops.prim.NumToTensor(torch.size(coefficients, 0))
    _24 = int(_23)
    _25 = ops.prim.NumToTensor(torch.size(_1, 1))
    _26 = int(_25)
    _27 = ops.prim.NumToTensor(torch.size(_1, 2))
    mixed_weight1 = torch.view(_22, [_24, _26, int(_27)])
    _28 = torch.cat([argument_1, layer_out0], 1)
    input4 = torch.unsqueeze(_28, 1)
    mixed_bias1 = torch.unsqueeze(torch.matmul(coefficients, _0), 1)
    _29 = torch.baddbmm(mixed_bias1, input4, mixed_weight1)
    return torch.squeeze(_29, 1)
