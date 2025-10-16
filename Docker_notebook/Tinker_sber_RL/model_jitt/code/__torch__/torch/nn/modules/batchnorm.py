class BatchNorm1d(Module):
  __parameters__ = []
  __buffers__ = ["running_mean", "running_var", "num_batches_tracked", ]
  running_mean : Tensor
  running_var : Tensor
  num_batches_tracked : Tensor
  training : bool
  _is_full_backward_hook : Optional[bool]
